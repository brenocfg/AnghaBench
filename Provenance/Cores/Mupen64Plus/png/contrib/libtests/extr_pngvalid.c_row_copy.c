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
typedef  unsigned int* png_const_bytep ;
typedef  unsigned int* png_bytep ;
typedef  unsigned int png_byte ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned int*,unsigned int*,unsigned int) ; 

__attribute__((used)) static void
row_copy(png_bytep toBuffer, png_const_bytep fromBuffer, unsigned int bitWidth,
      int littleendian)
{
   memcpy(toBuffer, fromBuffer, bitWidth >> 3);

   if ((bitWidth & 7) != 0)
   {
      unsigned int mask;

      toBuffer += bitWidth >> 3;
      fromBuffer += bitWidth >> 3;
      if (littleendian)
         mask = 0xff << (bitWidth & 7);
      else
         mask = 0xff >> (bitWidth & 7);
      *toBuffer = (png_byte)((*toBuffer & mask) | (*fromBuffer & ~mask));
   }
}