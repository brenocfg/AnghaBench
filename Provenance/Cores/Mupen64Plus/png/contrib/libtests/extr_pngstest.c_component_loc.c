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
typedef  int png_uint_32 ;
typedef  int png_byte ;

/* Variables and functions */
 int PNG_FORMAT_FLAG_AFIRST ; 
 int PNG_FORMAT_FLAG_ALPHA ; 
 int PNG_FORMAT_FLAG_BGR ; 
 int PNG_FORMAT_FLAG_COLOR ; 

__attribute__((used)) static png_byte
component_loc(png_byte loc[4], png_uint_32 format)
{
   /* Given a format return the number of channels and the location of
    * each channel.
    *
    * The mask 'loc' contains the component offset of the channels in the
    * following order.  Note that if 'format' is grayscale the entries 1-3 must
    * all contain the location of the gray channel.
    *
    * 0: alpha
    * 1: red or gray
    * 2: green or gray
    * 3: blue or gray
    */
   png_byte channels;

   if (format & PNG_FORMAT_FLAG_COLOR)
   {
      channels = 3;

      loc[2] = 1;

#     ifdef PNG_FORMAT_BGR_SUPPORTED
         if (format & PNG_FORMAT_FLAG_BGR)
         {
            loc[1] = 2;
            loc[3] = 0;
         }

         else
#     endif
      {
         loc[1] = 0;
         loc[3] = 2;
      }
   }

   else
   {
      channels = 1;
      loc[1] = loc[2] = loc[3] = 0;
   }

   if (format & PNG_FORMAT_FLAG_ALPHA)
   {
#     ifdef PNG_FORMAT_AFIRST_SUPPORTED
         if (format & PNG_FORMAT_FLAG_AFIRST)
         {
            loc[0] = 0;
            ++loc[1];
            ++loc[2];
            ++loc[3];
         }

         else
#     endif
         loc[0] = channels;

      ++channels;
   }

   else
      loc[0] = 4; /* not present */

   return channels;
}