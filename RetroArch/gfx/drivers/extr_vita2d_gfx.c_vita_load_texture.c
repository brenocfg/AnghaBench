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
struct vita2d_texture {int dummy; } ;
struct texture_image {unsigned int width; unsigned int height; int /*<<< orphan*/ * pixels; } ;
typedef  enum texture_filter_type { ____Placeholder_texture_filter_type } texture_filter_type ;

/* Variables and functions */
 int /*<<< orphan*/  SCE_GXM_TEXTURE_FILTER_LINEAR ; 
 int /*<<< orphan*/  SCE_GXM_TEXTURE_FORMAT_U8U8U8U8_ARGB ; 
 int TEXTURE_FILTER_LINEAR ; 
 int TEXTURE_FILTER_MIPMAP_LINEAR ; 
 int /*<<< orphan*/  memcpy_neon (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 struct vita2d_texture* vita2d_create_empty_texture_format (unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vita2d_texture_get_datap (struct vita2d_texture*) ; 
 unsigned int vita2d_texture_get_stride (struct vita2d_texture*) ; 
 int /*<<< orphan*/  vita2d_texture_set_filters (struct vita2d_texture*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uintptr_t vita_load_texture(void *video_data, void *data,
      bool threaded, enum texture_filter_type filter_type)
{
   unsigned int stride, pitch, j;
   uint32_t             *tex32    = NULL;
   const uint32_t *frame32        = NULL;
   struct texture_image *image    = (struct texture_image*)data;
   struct vita2d_texture *texture = vita2d_create_empty_texture_format(image->width,
     image->height,SCE_GXM_TEXTURE_FORMAT_U8U8U8U8_ARGB);

   if (!texture)
      return 0;

   if ((filter_type == TEXTURE_FILTER_MIPMAP_LINEAR) ||
      (filter_type == TEXTURE_FILTER_LINEAR))
      vita2d_texture_set_filters(texture,
            SCE_GXM_TEXTURE_FILTER_LINEAR,
            SCE_GXM_TEXTURE_FILTER_LINEAR);

   stride                      = vita2d_texture_get_stride(texture);
   stride                     /= 4;

   tex32                       = vita2d_texture_get_datap(texture);
   frame32                     = image->pixels;
   pitch                       = image->width;

   for (j = 0; j < image->height; j++)
         memcpy_neon(
               &tex32[j*stride],
               &frame32[j*pitch],
               pitch * sizeof(uint32_t));

   return (uintptr_t)texture;
}