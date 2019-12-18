#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ menu_linear_filter; } ;
struct TYPE_12__ {TYPE_3__ bools; } ;
typedef  TYPE_4__ settings_t ;
struct TYPE_9__ {unsigned int Width; unsigned int Height; int /*<<< orphan*/  Format; } ;
struct TYPE_14__ {int /*<<< orphan*/  sampler; TYPE_1__ desc; } ;
struct TYPE_10__ {TYPE_6__ texture; } ;
struct TYPE_13__ {int /*<<< orphan*/ ** samplers; TYPE_2__ menu; int /*<<< orphan*/  device; } ;
typedef  TYPE_5__ d3d10_video_t ;
typedef  int /*<<< orphan*/  DXGI_FORMAT ;

/* Variables and functions */
 int /*<<< orphan*/  DXGI_FORMAT_B8G8R8A8_UNORM ; 
 scalar_t__ DXGI_FORMAT_EX_A4R4G4B4_UNORM ; 
 size_t RARCH_FILTER_LINEAR ; 
 size_t RARCH_FILTER_NEAREST ; 
 size_t RARCH_WRAP_DEFAULT ; 
 TYPE_4__* config_get_ptr () ; 
 int /*<<< orphan*/  d3d10_init_texture (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  d3d10_update_texture (int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,TYPE_6__*) ; 

__attribute__((used)) static void d3d10_set_menu_texture_frame(
      void* data, const void* frame, bool rgb32, unsigned width, unsigned height, float alpha)
{
   d3d10_video_t* d3d10    = (d3d10_video_t*)data;
   settings_t*    settings = config_get_ptr();
   DXGI_FORMAT    format   = rgb32 ? DXGI_FORMAT_B8G8R8A8_UNORM :
      (DXGI_FORMAT)DXGI_FORMAT_EX_A4R4G4B4_UNORM;

   if (
         d3d10->menu.texture.desc.Width  != width ||
         d3d10->menu.texture.desc.Height != height)
   {
      d3d10->menu.texture.desc.Format = format;
      d3d10->menu.texture.desc.Width  = width;
      d3d10->menu.texture.desc.Height = height;
      d3d10_init_texture(d3d10->device, &d3d10->menu.texture);
   }

   d3d10_update_texture(d3d10->device, width, height, 0,
         format, frame, &d3d10->menu.texture);
   d3d10->menu.texture.sampler = d3d10->samplers
      [settings->bools.menu_linear_filter
      ? RARCH_FILTER_LINEAR
         : RARCH_FILTER_NEAREST][RARCH_WRAP_DEFAULT];
}