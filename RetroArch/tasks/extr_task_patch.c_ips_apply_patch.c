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
typedef  char uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  enum patch_error { ____Placeholder_patch_error } patch_error ;

/* Variables and functions */
 int PATCH_PATCH_INVALID ; 
 int PATCH_SUCCESS ; 
 int PATCH_UNKNOWN ; 
 int ips_alloc_targetdata (char const*,int,int,char**,int*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 

__attribute__((used)) static enum patch_error ips_apply_patch(
      const uint8_t *patchdata, uint64_t patchlen,
      const uint8_t *sourcedata, uint64_t sourcelength,
      uint8_t **targetdata, uint64_t *targetlength)
{
   uint32_t offset = 5;
   enum patch_error error_patch = PATCH_UNKNOWN;
   if (patchlen < 8 ||
         patchdata[0] != 'P' ||
         patchdata[1] != 'A' ||
         patchdata[2] != 'T' ||
         patchdata[3] != 'C' ||
         patchdata[4] != 'H')
      return PATCH_PATCH_INVALID;
   
   error_patch = ips_alloc_targetdata( patchdata,     patchlen,
                                       sourcelength,  targetdata,
                                                      targetlength);
   if ( error_patch != PATCH_SUCCESS)
      return error_patch;

   memcpy(*targetdata, sourcedata, (size_t)sourcelength);

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
            return PATCH_SUCCESS;
         else if (offset == patchlen - 3)
         {
            uint32_t size = patchdata[offset++] << 16;
            size |= patchdata[offset++] << 8;
            size |= patchdata[offset++] << 0;
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
            (*targetdata)[address++] = patchdata[offset++];
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
            (*targetdata)[address++] = patchdata[offset];

         offset++;
      }
   }

   return PATCH_PATCH_INVALID;
}