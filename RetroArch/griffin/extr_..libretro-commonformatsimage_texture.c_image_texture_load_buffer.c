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
struct texture_image {int supports_rgba; scalar_t__ height; scalar_t__ width; int /*<<< orphan*/ * pixels; } ;
typedef  enum image_type_enum { ____Placeholder_image_type_enum } image_type_enum ;

/* Variables and functions */
 int IMAGE_TYPE_NONE ; 
 scalar_t__ image_texture_load_internal (int,void*,size_t,struct texture_image*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  image_texture_set_color_shifts (unsigned int*,unsigned int*,unsigned int*,unsigned int*,struct texture_image*) ; 

bool image_texture_load_buffer(struct texture_image *out_img,
   enum image_type_enum type, void *buffer, size_t buffer_len)
{
   unsigned r_shift, g_shift, b_shift, a_shift;
   image_texture_set_color_shifts(&r_shift, &g_shift, &b_shift,
      &a_shift, out_img);

   if (type != IMAGE_TYPE_NONE)
   {
      if (image_texture_load_internal(
         type, buffer, buffer_len, out_img,
         a_shift, r_shift, g_shift, b_shift))
      {
         return true;
      }
   }

   out_img->supports_rgba = false;
   out_img->pixels = NULL;
   out_img->width = 0;
   out_img->height = 0;

   return false;
}