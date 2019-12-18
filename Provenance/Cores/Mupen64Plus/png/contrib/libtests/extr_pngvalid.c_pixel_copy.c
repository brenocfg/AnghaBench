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
typedef  unsigned int png_uint_32 ;
typedef  unsigned int* png_const_bytep ;
typedef  unsigned int* png_bytep ;
typedef  unsigned int png_byte ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (unsigned int*,unsigned int*,unsigned int) ; 

__attribute__((used)) static void
pixel_copy(png_bytep toBuffer, png_uint_32 toIndex,
   png_const_bytep fromBuffer, png_uint_32 fromIndex, unsigned int pixelSize,
   int littleendian)
{
   /* Assume we can multiply by 'size' without overflow because we are
    * just working in a single buffer.
    */
   toIndex *= pixelSize;
   fromIndex *= pixelSize;
   if (pixelSize < 8) /* Sub-byte */
   {
      /* Mask to select the location of the copied pixel: */
      unsigned int destMask = ((1U<<pixelSize)-1) <<
         (littleendian ? toIndex&7 : 8-pixelSize-(toIndex&7));
      /* The following read the entire pixels and clears the extra: */
      unsigned int destByte = toBuffer[toIndex >> 3] & ~destMask;
      unsigned int sourceByte = fromBuffer[fromIndex >> 3];

      /* Don't rely on << or >> supporting '0' here, just in case: */
      fromIndex &= 7;
      if (littleendian)
      {
         if (fromIndex > 0) sourceByte >>= fromIndex;
         if ((toIndex & 7) > 0) sourceByte <<= toIndex & 7;
      }

      else
      {
         if (fromIndex > 0) sourceByte <<= fromIndex;
         if ((toIndex & 7) > 0) sourceByte >>= toIndex & 7;
      }

      toBuffer[toIndex >> 3] = (png_byte)(destByte | (sourceByte & destMask));
   }
   else /* One or more bytes */
      memmove(toBuffer+(toIndex>>3), fromBuffer+(fromIndex>>3), pixelSize>>3);
}