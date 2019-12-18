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
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  enum patch_error { ____Placeholder_patch_error } patch_error ;

/* Variables and functions */
 int PATCH_PATCH_INVALID ; 
 int PATCH_SUCCESS ; 
 int PATCH_TARGET_ALLOC_FAILED ; 
 int /*<<< orphan*/  free (int*) ; 
 scalar_t__ malloc (size_t) ; 

__attribute__((used)) static enum patch_error ips_alloc_targetdata(
      const uint8_t *patchdata, uint64_t patchlen,
      uint64_t sourcelength,
      uint8_t **targetdata, uint64_t *targetlength)
{
   uint8_t *prov_alloc;
   uint32_t offset = 5;
   *targetlength = sourcelength;

   for (;;)
   {
      uint32_t address;
      unsigned length;

      if (offset > patchlen - 3)
         break;

      address  = patchdata[offset++] << 16;
      address |= patchdata[offset++] << 8;
      address |= patchdata[offset++] << 0;

      if (address == 0x454f46) /* EOF */
      {
         if (offset == patchlen)
         {
            prov_alloc=(uint8_t*)malloc((size_t)*targetlength);
            if (!prov_alloc)
               return PATCH_TARGET_ALLOC_FAILED;
            free(*targetdata);
            *targetdata=prov_alloc;
            return PATCH_SUCCESS;
         }
         else if (offset == patchlen - 3)
         {
            uint32_t size = patchdata[offset++] << 16;
            size |= patchdata[offset++] << 8;
            size |= patchdata[offset++] << 0;
            *targetlength = size;
            prov_alloc=(uint8_t*)malloc((size_t)*targetlength);
            if (!prov_alloc)
               return PATCH_TARGET_ALLOC_FAILED;
            free(*targetdata);
            *targetdata=prov_alloc;
            return PATCH_SUCCESS;
         }
      }

      if (offset > patchlen - 2)
         break;

      length  = patchdata[offset++] << 8;
      length |= patchdata[offset++] << 0;

      if (length) /* Copy */
      {
         if (offset > patchlen - length)
            break;

         while (length--)
         {
            address++;
            offset++;
         }
      }
      else /* RLE */
      {
         if (offset > patchlen - 3)
            break;

         length  = patchdata[offset++] << 8;
         length |= patchdata[offset++] << 0;

         if (length == 0) /* Illegal */
            break;

         while (length--)
            address++;

         offset++;
      }

      if (address > *targetlength)
         *targetlength = address;
   }

   return PATCH_PATCH_INVALID;
}