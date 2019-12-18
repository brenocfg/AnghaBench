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
struct nbio_t {int dummy; } ;
typedef  enum image_type_enum { ____Placeholder_image_type_enum } image_type_enum ;

/* Variables and functions */
 int IMAGE_TYPE_NONE ; 
 int /*<<< orphan*/  NBIO_READ ; 
 int image_texture_get_type (char const*) ; 
 scalar_t__ image_texture_load_internal (int,void*,size_t,struct texture_image*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  image_texture_set_color_shifts (unsigned int*,unsigned int*,unsigned int*,unsigned int*,struct texture_image*) ; 
 int /*<<< orphan*/  nbio_begin_read (struct nbio_t*) ; 
 int /*<<< orphan*/  nbio_free (struct nbio_t*) ; 
 void* nbio_get_ptr (struct nbio_t*,size_t*) ; 
 int /*<<< orphan*/  nbio_iterate (struct nbio_t*) ; 
 scalar_t__ nbio_open (char const*,int /*<<< orphan*/ ) ; 

bool image_texture_load(struct texture_image *out_img,
      const char *path)
{
   unsigned r_shift, g_shift, b_shift, a_shift;
   size_t file_len             = 0;
   struct nbio_t      *handle  = NULL;
   void                   *ptr = NULL;
   enum image_type_enum type  = image_texture_get_type(path);

   image_texture_set_color_shifts(&r_shift, &g_shift, &b_shift,
         &a_shift, out_img);

   if (type != IMAGE_TYPE_NONE)
   {
      handle = (struct nbio_t*)nbio_open(path, NBIO_READ);
      if (!handle)
         goto error;
      nbio_begin_read(handle);

      while (!nbio_iterate(handle));

      ptr = nbio_get_ptr(handle, &file_len);

      if (!ptr)
         goto error;

      if (image_texture_load_internal(
               type,
               ptr, file_len, out_img,
               a_shift, r_shift, g_shift, b_shift))
         goto success;
   }

error:
   out_img->supports_rgba = false;
   out_img->pixels        = NULL;
   out_img->width         = 0;
   out_img->height        = 0;
   if (handle)
      nbio_free(handle);

   return false;

success:
   if (handle)
      nbio_free(handle);

   return true;
}