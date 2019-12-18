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
typedef  int /*<<< orphan*/  uint32_t ;
struct texture_image {int /*<<< orphan*/ * pixels; scalar_t__ height; scalar_t__ width; int /*<<< orphan*/  supports_rgba; } ;
typedef  enum texture_filter_type { ____Placeholder_texture_filter_type } texture_filter_type ;
typedef  enum gfx_wrap_type { ____Placeholder_gfx_wrap_type } gfx_wrap_type ;
typedef  int /*<<< orphan*/  GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*,char const*) ; 
 unsigned int RARCH_FILTER_NEAREST ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char const*) ; 
 int TEXTURE_FILTER_LINEAR ; 
 int TEXTURE_FILTER_MIPMAP_LINEAR ; 
 int TEXTURE_FILTER_MIPMAP_NEAREST ; 
 int TEXTURE_FILTER_NEAREST ; 
 int /*<<< orphan*/  gl_load_texture_data (int /*<<< orphan*/ ,int,int,int,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  image_texture_free (struct texture_image*) ; 
 int /*<<< orphan*/  image_texture_load (struct texture_image*,char const*) ; 
 int /*<<< orphan*/  video_driver_supports_rgba () ; 

__attribute__((used)) static bool gl2_add_lut(
      const char *lut_path,
      bool lut_mipmap,
      unsigned lut_filter,
      enum gfx_wrap_type lut_wrap_type,
      unsigned i, GLuint *textures_lut)
{
   struct texture_image img;
   enum texture_filter_type filter_type = TEXTURE_FILTER_LINEAR;

   img.width         = 0;
   img.height        = 0;
   img.pixels        = NULL;
   img.supports_rgba = video_driver_supports_rgba();

   if (!image_texture_load(&img, lut_path))
   {
      RARCH_ERR("[GL]: Failed to load texture image from: \"%s\"\n",
            lut_path);
      return false;
   }

   RARCH_LOG("[GL]: Loaded texture image from: \"%s\" ...\n",
         lut_path);

   if (lut_filter == RARCH_FILTER_NEAREST)
      filter_type = TEXTURE_FILTER_NEAREST;

   if (lut_mipmap)
   {
      if (filter_type == TEXTURE_FILTER_NEAREST)
         filter_type = TEXTURE_FILTER_MIPMAP_NEAREST;
      else
         filter_type = TEXTURE_FILTER_MIPMAP_LINEAR;
   }

   gl_load_texture_data(
         textures_lut[i],
         lut_wrap_type,
         filter_type, 4,
         img.width, img.height,
         img.pixels, sizeof(uint32_t));
   image_texture_free(&img);

   return true;
}