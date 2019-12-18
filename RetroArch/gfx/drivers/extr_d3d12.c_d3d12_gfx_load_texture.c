#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct texture_image {int /*<<< orphan*/  pixels; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  enum texture_filter_type { ____Placeholder_texture_filter_type } texture_filter_type ;
struct TYPE_8__ {int /*<<< orphan*/  srv_heap; } ;
struct TYPE_9__ {int /*<<< orphan*/  device; TYPE_2__ desc; int /*<<< orphan*/ ** samplers; } ;
typedef  TYPE_3__ d3d12_video_t ;
struct TYPE_7__ {int /*<<< orphan*/  Format; int /*<<< orphan*/  Height; int /*<<< orphan*/  Width; void* MipLevels; } ;
struct TYPE_10__ {int /*<<< orphan*/ * srv_heap; TYPE_1__ desc; int /*<<< orphan*/  sampler; } ;
typedef  TYPE_4__ d3d12_texture_t ;

/* Variables and functions */
 int /*<<< orphan*/  DXGI_FORMAT_B8G8R8A8_UNORM ; 
 size_t RARCH_FILTER_LINEAR ; 
 size_t RARCH_FILTER_NEAREST ; 
 size_t RARCH_WRAP_EDGE ; 
#define  TEXTURE_FILTER_LINEAR 131 
#define  TEXTURE_FILTER_MIPMAP_LINEAR 130 
#define  TEXTURE_FILTER_MIPMAP_NEAREST 129 
#define  TEXTURE_FILTER_NEAREST 128 
 void* UINT16_MAX ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  d3d12_init_texture (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  d3d12_update_texture (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static uintptr_t d3d12_gfx_load_texture(
      void* video_data, void* data, bool threaded,
      enum texture_filter_type filter_type)
{
   d3d12_texture_t*      texture = NULL;
   d3d12_video_t*        d3d12   = (d3d12_video_t*)video_data;
   struct texture_image* image   = (struct texture_image*)data;

   if (!d3d12)
      return 0;

   texture = (d3d12_texture_t*)calloc(1, sizeof(*texture));

   if (!texture)
      return 0;

   switch (filter_type)
   {
      case TEXTURE_FILTER_MIPMAP_LINEAR:
         texture->desc.MipLevels = UINT16_MAX;
      case TEXTURE_FILTER_LINEAR:
         texture->sampler = d3d12->samplers[
            RARCH_FILTER_LINEAR][RARCH_WRAP_EDGE];
         break;
      case TEXTURE_FILTER_MIPMAP_NEAREST:
         texture->desc.MipLevels = UINT16_MAX;
      case TEXTURE_FILTER_NEAREST:
         texture->sampler = d3d12->samplers[
            RARCH_FILTER_NEAREST][RARCH_WRAP_EDGE];
         break;
   }

   texture->desc.Width  = image->width;
   texture->desc.Height = image->height;
   texture->desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
   texture->srv_heap    = &d3d12->desc.srv_heap;

   d3d12_init_texture(d3d12->device, texture);

   d3d12_update_texture(
         image->width, image->height, 0,
         DXGI_FORMAT_B8G8R8A8_UNORM, image->pixels, texture);

   return (uintptr_t)texture;
}