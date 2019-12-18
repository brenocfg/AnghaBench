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
typedef  int /*<<< orphan*/  vk_t ;
typedef  int /*<<< orphan*/  const uint32_t ;
struct vk_texture {int default_smooth; int mipmap; } ;
struct texture_image {int width; int height; int /*<<< orphan*/  const* pixels; } ;
typedef  enum texture_filter_type { ____Placeholder_texture_filter_type } texture_filter_type ;

/* Variables and functions */
#define  T0 129 
#define  T1 128 
 int TEXTURE_FILTER_LINEAR ; 
 int TEXTURE_FILTER_MIPMAP_LINEAR ; 
 int /*<<< orphan*/  VK_FORMAT_B8G8R8A8_UNORM ; 
 int /*<<< orphan*/  VULKAN_TEXTURE_STATIC ; 
 scalar_t__ calloc (int,int) ; 
 struct vk_texture vulkan_create_texture (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uintptr_t vulkan_load_texture(void *video_data, void *data,
      bool threaded, enum texture_filter_type filter_type)
{
   struct vk_texture *texture  = NULL;
   vk_t *vk                    = (vk_t*)video_data;
   struct texture_image *image = (struct texture_image*)data;
   if (!image)
      return 0;

   texture                     = (struct vk_texture*)
      calloc(1, sizeof(*texture));

   if (!texture)
      return 0;

   if (!image->pixels || !image->width || !image->height)
   {
      /* Create a dummy texture instead. */
#define T0 0xff000000u
#define T1 0xffffffffu
      static const uint32_t checkerboard[] = {
         T0, T1, T0, T1, T0, T1, T0, T1,
         T1, T0, T1, T0, T1, T0, T1, T0,
         T0, T1, T0, T1, T0, T1, T0, T1,
         T1, T0, T1, T0, T1, T0, T1, T0,
         T0, T1, T0, T1, T0, T1, T0, T1,
         T1, T0, T1, T0, T1, T0, T1, T0,
         T0, T1, T0, T1, T0, T1, T0, T1,
         T1, T0, T1, T0, T1, T0, T1, T0,
      };
#undef T0
#undef T1
      *texture = vulkan_create_texture(vk, NULL,
            8, 8, VK_FORMAT_B8G8R8A8_UNORM,
            checkerboard, NULL, VULKAN_TEXTURE_STATIC);
      texture->default_smooth = false;
      texture->mipmap = false;
   }
   else
   {
      *texture = vulkan_create_texture(vk, NULL,
            image->width, image->height, VK_FORMAT_B8G8R8A8_UNORM,
            image->pixels, NULL, VULKAN_TEXTURE_STATIC);

      texture->default_smooth =
         filter_type == TEXTURE_FILTER_MIPMAP_LINEAR || filter_type == TEXTURE_FILTER_LINEAR;
      texture->mipmap = filter_type == TEXTURE_FILTER_MIPMAP_LINEAR;
   }

   return (uintptr_t)texture;
}