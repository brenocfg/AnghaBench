#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uLong ;
typedef  scalar_t__ uInt ;
typedef  scalar_t__ png_uint_32 ;
typedef  TYPE_1__* png_structrp ;
typedef  scalar_t__ png_size_t ;
typedef  int /*<<< orphan*/  png_const_bytep ;
struct TYPE_3__ {int flags; scalar_t__ crc; int /*<<< orphan*/  chunk_name; } ;

/* Variables and functions */
 scalar_t__ PNG_CHUNK_ANCILLARY (int /*<<< orphan*/ ) ; 
 int PNG_FLAG_CRC_ANCILLARY_MASK ; 
 int PNG_FLAG_CRC_ANCILLARY_NOWARN ; 
 int PNG_FLAG_CRC_ANCILLARY_USE ; 
 int PNG_FLAG_CRC_CRITICAL_IGNORE ; 
 scalar_t__ crc32 (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

void /* PRIVATE */
png_calculate_crc(png_structrp png_ptr, png_const_bytep ptr, png_size_t length)
{
   int need_crc = 1;

   if (PNG_CHUNK_ANCILLARY(png_ptr->chunk_name) != 0)
   {
      if ((png_ptr->flags & PNG_FLAG_CRC_ANCILLARY_MASK) ==
          (PNG_FLAG_CRC_ANCILLARY_USE | PNG_FLAG_CRC_ANCILLARY_NOWARN))
         need_crc = 0;
   }

   else /* critical */
   {
      if ((png_ptr->flags & PNG_FLAG_CRC_CRITICAL_IGNORE) != 0)
         need_crc = 0;
   }

   /* 'uLong' is defined in zlib.h as unsigned long; this means that on some
    * systems it is a 64-bit value.  crc32, however, returns 32 bits so the
    * following cast is safe.  'uInt' may be no more than 16 bits, so it is
    * necessary to perform a loop here.
    */
   if (need_crc != 0 && length > 0)
   {
      uLong crc = png_ptr->crc; /* Should never issue a warning */

      do
      {
         uInt safe_length = (uInt)length;
#ifndef __COVERITY__
         if (safe_length == 0)
            safe_length = (uInt)-1; /* evil, but safe */
#endif

         crc = crc32(crc, ptr, safe_length);

         /* The following should never issue compiler warnings; if they do the
          * target system has characteristics that will probably violate other
          * assumptions within the libpng code.
          */
         ptr += safe_length;
         length -= safe_length;
      }
      while (length > 0);

      /* And the following is always safe because the crc is only 32 bits. */
      png_ptr->crc = (png_uint_32)crc;
   }
}