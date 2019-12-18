#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int uint64_t ;
typedef  size_t uint32_t ;
struct bps_data {size_t const* modify_data; size_t const* source_data; size_t* target_data; int modify_length; int source_length; int target_length; int modify_offset; size_t modify_checksum; size_t source_checksum; size_t target_checksum; size_t output_offset; scalar_t__ target_offset; scalar_t__ source_offset; scalar_t__ target_relative_offset; scalar_t__ source_relative_offset; } ;
typedef  enum patch_error { ____Placeholder_patch_error } patch_error ;

/* Variables and functions */
 int PATCH_PATCH_CHECKSUM_INVALID ; 
 int PATCH_PATCH_INVALID_HEADER ; 
 int PATCH_PATCH_TOO_SMALL ; 
 int PATCH_SOURCE_CHECKSUM_INVALID ; 
 int PATCH_SOURCE_TOO_SMALL ; 
 int PATCH_SUCCESS ; 
 int PATCH_TARGET_ALLOC_FAILED ; 
 int PATCH_TARGET_CHECKSUM_INVALID ; 
#define  SOURCE_COPY 131 
#define  SOURCE_READ 130 
#define  TARGET_COPY 129 
#define  TARGET_READ 128 
 size_t bps_decode (struct bps_data*) ; 
 size_t bps_read (struct bps_data*) ; 
 int /*<<< orphan*/  bps_write (struct bps_data*,size_t) ; 
 size_t encoding_crc32 (int /*<<< orphan*/ ,size_t*,size_t) ; 
 int /*<<< orphan*/  free (size_t*) ; 
 scalar_t__ malloc (size_t) ; 

__attribute__((used)) static enum patch_error bps_apply_patch(
      const uint8_t *modify_data, uint64_t modify_length,
      const uint8_t *source_data, uint64_t source_length,
      uint8_t **target_data, uint64_t *target_length)
{
   size_t i;
   uint32_t checksum;
   size_t modify_source_size;
   size_t modify_target_size;
   size_t modify_markup_size;
   struct bps_data bps;
   uint32_t modify_source_checksum = 0;
   uint32_t modify_target_checksum = 0;
   uint32_t modify_modify_checksum = 0;

   if (modify_length < 19)
      return PATCH_PATCH_TOO_SMALL;

   bps.modify_data            = modify_data;
   bps.source_data            = source_data;
   bps.target_data            = *target_data;
   bps.modify_length          = modify_length;
   bps.source_length          = source_length;
   bps.target_length          = *target_length;
   bps.modify_offset          = 0;
   bps.source_offset          = 0;
   bps.target_offset          = 0;
   bps.modify_checksum        = ~0;
   bps.source_checksum        = 0;
   bps.target_checksum        = ~0;
   bps.source_relative_offset = 0;
   bps.target_relative_offset = 0;
   bps.output_offset          = 0;

   if (  (bps_read(&bps) != 'B') ||
         (bps_read(&bps) != 'P') ||
         (bps_read(&bps) != 'S') ||
         (bps_read(&bps) != '1'))
      return PATCH_PATCH_INVALID_HEADER;

   modify_source_size  = bps_decode(&bps);
   modify_target_size  = bps_decode(&bps);
   modify_markup_size  = bps_decode(&bps);

   for (i = 0; i < modify_markup_size; i++)
      bps_read(&bps);

   if (modify_source_size > bps.source_length)
      return PATCH_SOURCE_TOO_SMALL;
   if (modify_target_size > bps.target_length){
      uint8_t *prov=(uint8_t*)malloc((size_t)modify_target_size);
      if (prov!=NULL){
         free(*target_data);
	      bps.target_data=prov;
         *target_data=prov;
         bps.target_length=modify_target_size;
      }else
         return PATCH_TARGET_ALLOC_FAILED;
   }

   while (bps.modify_offset < bps.modify_length - 12)
   {
      size_t length = bps_decode(&bps);
      unsigned mode = length & 3;

      length = (length >> 2) + 1;

      switch (mode)
      {
         case SOURCE_READ:
            while (length--)
               bps_write(&bps, bps.source_data[bps.output_offset]);
            break;

         case TARGET_READ:
            while (length--)
               bps_write(&bps, bps_read(&bps));
            break;

         case SOURCE_COPY:
         case TARGET_COPY:
         {
            int    offset = (int)bps_decode(&bps);
            bool negative = offset & 1;

            offset >>= 1;

            if (negative)
               offset = -offset;

            if (mode == SOURCE_COPY)
            {
               bps.source_offset += offset;
               while (length--)
                  bps_write(&bps, bps.source_data[bps.source_offset++]);
            }
            else
            {
               bps.target_offset += offset;
               while (length--)
                  bps_write(&bps, bps.target_data[bps.target_offset++]);
               break;
            }
            break;
         }
      }
   }

   for (i = 0; i < 32; i += 8)
      modify_source_checksum |= bps_read(&bps) << i;
   for (i = 0; i < 32; i += 8)
      modify_target_checksum |= bps_read(&bps) << i;

   checksum = ~bps.modify_checksum;
   for (i = 0; i < 32; i += 8)
      modify_modify_checksum |= bps_read(&bps) << i;

   bps.source_checksum = encoding_crc32(0,
         bps.source_data, bps.source_length);
   bps.target_checksum = ~bps.target_checksum;

   if (bps.source_checksum != modify_source_checksum)
      return PATCH_SOURCE_CHECKSUM_INVALID;

   if (bps.target_checksum != modify_target_checksum)
      return PATCH_TARGET_CHECKSUM_INVALID;

   if (checksum != modify_modify_checksum)
      return PATCH_PATCH_CHECKSUM_INVALID;

   *target_length = modify_target_size;

   return PATCH_SUCCESS;
}