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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct texture_image {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  pixels; } ;
typedef  enum image_type_enum { ____Placeholder_image_type_enum } image_type_enum ;

/* Variables and functions */
 int IMAGE_PROCESS_ERROR ; 
 int IMAGE_PROCESS_ERROR_END ; 
 int IMAGE_PROCESS_NEXT ; 
 int /*<<< orphan*/  image_texture_color_convert (unsigned int,unsigned int,unsigned int,unsigned int,struct texture_image*) ; 
 int /*<<< orphan*/  image_texture_free (struct texture_image*) ; 
 int /*<<< orphan*/  image_texture_internal_gx_convert_texture32 (struct texture_image*) ; 
 int /*<<< orphan*/  image_transfer_free (void*,int) ; 
 int /*<<< orphan*/  image_transfer_is_valid (void*,int) ; 
 scalar_t__ image_transfer_iterate (void*,int) ; 
 void* image_transfer_new (int) ; 
 int image_transfer_process (void*,int,int /*<<< orphan*/ **,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  image_transfer_set_buffer_ptr (void*,int,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  image_transfer_start (void*,int) ; 

__attribute__((used)) static bool image_texture_load_internal(
      enum image_type_enum type,
      void *ptr,
      size_t len,
      struct texture_image *out_img,
      unsigned a_shift, unsigned r_shift,
      unsigned g_shift, unsigned b_shift)
{
   int ret;
   bool success = false;
   void *img    = image_transfer_new(type);

   if (!img)
      goto end;

   image_transfer_set_buffer_ptr(img, type, (uint8_t*)ptr, len);

   if (!image_transfer_start(img, type))
      goto end;

   while (image_transfer_iterate(img, type));

   if (!image_transfer_is_valid(img, type))
      goto end;

   do
   {
      ret = image_transfer_process(img, type,
            (uint32_t**)&out_img->pixels, len, &out_img->width,
            &out_img->height);
   }while(ret == IMAGE_PROCESS_NEXT);

   if (ret == IMAGE_PROCESS_ERROR || ret == IMAGE_PROCESS_ERROR_END)
      goto end;

   image_texture_color_convert(r_shift, g_shift, b_shift,
         a_shift, out_img);

#ifdef GEKKO
   if (!image_texture_internal_gx_convert_texture32(out_img))
   {
      image_texture_free(out_img);
      goto end;
   }
#endif

   success = true;

end:
   if (img)
      image_transfer_free(img, type);

   return success;
}