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
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct rpng_process {int* decoded_scanline; int* inflate_buf; unsigned int pitch; unsigned int bpp; int* prev_scanline; int /*<<< orphan*/  palette; } ;
struct png_ihdr {int color_type; int /*<<< orphan*/  depth; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int IMAGE_PROCESS_ERROR_END ; 
 int IMAGE_PROCESS_NEXT ; 
#define  PNG_FILTER_AVERAGE 137 
#define  PNG_FILTER_NONE 136 
#define  PNG_FILTER_PAETH 135 
#define  PNG_FILTER_SUB 134 
#define  PNG_FILTER_UP 133 
#define  PNG_IHDR_COLOR_GRAY 132 
#define  PNG_IHDR_COLOR_GRAY_ALPHA 131 
#define  PNG_IHDR_COLOR_PLT 130 
#define  PNG_IHDR_COLOR_RGB 129 
#define  PNG_IHDR_COLOR_RGBA 128 
 int /*<<< orphan*/  memcpy (int*,int*,unsigned int) ; 
 void* paeth (int,int,int) ; 
 int /*<<< orphan*/  png_reverse_filter_copy_line_bw (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_reverse_filter_copy_line_gray_alpha (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_reverse_filter_copy_line_plt (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_reverse_filter_copy_line_rgb (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_reverse_filter_copy_line_rgba (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int png_reverse_filter_copy_line(uint32_t *data, const struct png_ihdr *ihdr,
      struct rpng_process *pngp, unsigned filter)
{
   unsigned i;

   switch (filter)
   {
      case PNG_FILTER_NONE:
         memcpy(pngp->decoded_scanline, pngp->inflate_buf, pngp->pitch);
         break;
      case PNG_FILTER_SUB:
         for (i = 0; i < pngp->bpp; i++)
            pngp->decoded_scanline[i] = pngp->inflate_buf[i];
         for (i = pngp->bpp; i < pngp->pitch; i++)
            pngp->decoded_scanline[i] = pngp->decoded_scanline[i - pngp->bpp] + pngp->inflate_buf[i];
         break;
      case PNG_FILTER_UP:
         for (i = 0; i < pngp->pitch; i++)
            pngp->decoded_scanline[i] = pngp->prev_scanline[i] + pngp->inflate_buf[i];
         break;
      case PNG_FILTER_AVERAGE:
         for (i = 0; i < pngp->bpp; i++)
         {
            uint8_t avg = pngp->prev_scanline[i] >> 1;
            pngp->decoded_scanline[i] = avg + pngp->inflate_buf[i];
         }
         for (i = pngp->bpp; i < pngp->pitch; i++)
         {
            uint8_t avg = (pngp->decoded_scanline[i - pngp->bpp] + pngp->prev_scanline[i]) >> 1;
            pngp->decoded_scanline[i] = avg + pngp->inflate_buf[i];
         }
         break;
      case PNG_FILTER_PAETH:
         for (i = 0; i < pngp->bpp; i++)
            pngp->decoded_scanline[i] = paeth(0, pngp->prev_scanline[i], 0) + pngp->inflate_buf[i];
         for (i = pngp->bpp; i < pngp->pitch; i++)
            pngp->decoded_scanline[i] = paeth(pngp->decoded_scanline[i - pngp->bpp],
                  pngp->prev_scanline[i], pngp->prev_scanline[i - pngp->bpp]) + pngp->inflate_buf[i];
         break;

      default:
         return IMAGE_PROCESS_ERROR_END;
   }

   switch (ihdr->color_type)
   {
      case PNG_IHDR_COLOR_GRAY:
         png_reverse_filter_copy_line_bw(data, pngp->decoded_scanline, ihdr->width, ihdr->depth);
         break;
      case PNG_IHDR_COLOR_RGB:
         png_reverse_filter_copy_line_rgb(data, pngp->decoded_scanline, ihdr->width, ihdr->depth);
         break;
      case PNG_IHDR_COLOR_PLT:
         png_reverse_filter_copy_line_plt(data, pngp->decoded_scanline, ihdr->width,
               ihdr->depth, pngp->palette);
         break;
      case PNG_IHDR_COLOR_GRAY_ALPHA:
         png_reverse_filter_copy_line_gray_alpha(data, pngp->decoded_scanline, ihdr->width,
               ihdr->depth);
         break;
      case PNG_IHDR_COLOR_RGBA:
         png_reverse_filter_copy_line_rgba(data, pngp->decoded_scanline, ihdr->width, ihdr->depth);
         break;
   }

   memcpy(pngp->prev_scanline, pngp->decoded_scanline, pngp->pitch);

   return IMAGE_PROCESS_NEXT;
}