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
typedef  size_t png_byte ;

/* Variables and functions */
 int PNG_INTERLACE_NONE ; 
 char** colour_types ; 
 size_t safecat (char*,size_t,size_t,char*) ; 
 size_t safecatn (char*,size_t,size_t,int) ; 

__attribute__((used)) static size_t
standard_name(char *buffer, size_t bufsize, size_t pos, png_byte colour_type,
    int bit_depth, unsigned int npalette, int interlace_type,
    png_uint_32 w, png_uint_32 h, int do_interlace)
{
   pos = safecat(buffer, bufsize, pos, colour_types[colour_type]);
   if (colour_type == 3) /* must have a palette */
   {
      pos = safecat(buffer, bufsize, pos, "[");
      pos = safecatn(buffer, bufsize, pos, npalette);
      pos = safecat(buffer, bufsize, pos, "]");
   }

   else if (npalette != 0)
      pos = safecat(buffer, bufsize, pos, "+tRNS");

   pos = safecat(buffer, bufsize, pos, " ");
   pos = safecatn(buffer, bufsize, pos, bit_depth);
   pos = safecat(buffer, bufsize, pos, " bit");

   if (interlace_type != PNG_INTERLACE_NONE)
   {
      pos = safecat(buffer, bufsize, pos, " interlaced");
      if (do_interlace)
         pos = safecat(buffer, bufsize, pos, "(pngvalid)");
      else
         pos = safecat(buffer, bufsize, pos, "(libpng)");
   }

   if (w > 0 || h > 0)
   {
      pos = safecat(buffer, bufsize, pos, " ");
      pos = safecatn(buffer, bufsize, pos, w);
      pos = safecat(buffer, bufsize, pos, "x");
      pos = safecatn(buffer, bufsize, pos, h);
   }

   return pos;
}