#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_16__ {scalar_t__ menu_linear_filter; } ;
struct TYPE_17__ {TYPE_4__ bools; } ;
typedef  TYPE_5__ settings_t ;
struct TYPE_13__ {unsigned int Width; unsigned int Height; int /*<<< orphan*/  Format; } ;
struct TYPE_21__ {int /*<<< orphan*/  sampler; int /*<<< orphan*/ * srv_heap; TYPE_1__ desc; } ;
struct TYPE_15__ {float alpha; TYPE_9__ texture; int /*<<< orphan*/  vbo; } ;
struct TYPE_14__ {int /*<<< orphan*/  srv_heap; } ;
struct TYPE_18__ {int /*<<< orphan*/ ** samplers; TYPE_3__ menu; int /*<<< orphan*/  device; TYPE_2__ desc; } ;
typedef  TYPE_6__ d3d12_video_t ;
struct TYPE_19__ {float* color; } ;
typedef  TYPE_7__ d3d12_vertex_t ;
struct TYPE_20__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  DXGI_FORMAT ;
typedef  TYPE_8__ D3D12_RANGE ;

/* Variables and functions */
 int /*<<< orphan*/  D3D12Map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_8__*,void**) ; 
 int /*<<< orphan*/  D3D12Unmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DXGI_FORMAT_B8G8R8A8_UNORM ; 
 scalar_t__ DXGI_FORMAT_EX_A4R4G4B4_UNORM ; 
 size_t RARCH_FILTER_LINEAR ; 
 size_t RARCH_FILTER_NEAREST ; 
 size_t RARCH_WRAP_DEFAULT ; 
 TYPE_5__* config_get_ptr () ; 
 int /*<<< orphan*/  d3d12_init_texture (int /*<<< orphan*/ ,TYPE_9__*) ; 
 int /*<<< orphan*/  d3d12_update_texture (unsigned int,unsigned int,int,int /*<<< orphan*/ ,void const*,TYPE_9__*) ; 

__attribute__((used)) static void d3d12_set_menu_texture_frame(
      void* data, const void* frame, bool rgb32,
      unsigned width, unsigned height, float alpha)
{
   d3d12_video_t* d3d12    = (d3d12_video_t*)data;
   settings_t*    settings = config_get_ptr();
   int            pitch    = width *
      (rgb32 ? sizeof(uint32_t) : sizeof(uint16_t));
   DXGI_FORMAT    format   = rgb32 ? DXGI_FORMAT_B8G8R8A8_UNORM
      : (DXGI_FORMAT)DXGI_FORMAT_EX_A4R4G4B4_UNORM;

   if (
         d3d12->menu.texture.desc.Width  != width ||
         d3d12->menu.texture.desc.Height != height)
   {
      d3d12->menu.texture.desc.Width  = width;
      d3d12->menu.texture.desc.Height = height;
      d3d12->menu.texture.desc.Format = format;
      d3d12->menu.texture.srv_heap    = &d3d12->desc.srv_heap;
      d3d12_init_texture(d3d12->device, &d3d12->menu.texture);
   }

   d3d12_update_texture(width, height, pitch,
         format, frame, &d3d12->menu.texture);

   d3d12->menu.alpha = alpha;

   {
      D3D12_RANGE     read_range = { 0, 0 };
      d3d12_vertex_t* v          = NULL;

      D3D12Map(d3d12->menu.vbo, 0, &read_range, (void**)&v);
      v[0].color[3] = alpha;
      v[1].color[3] = alpha;
      v[2].color[3] = alpha;
      v[3].color[3] = alpha;
      D3D12Unmap(d3d12->menu.vbo, 0, NULL);
   }

   d3d12->menu.texture.sampler = settings->bools.menu_linear_filter
      ? d3d12->samplers[RARCH_FILTER_LINEAR][RARCH_WRAP_DEFAULT]
      : d3d12->samplers[RARCH_FILTER_NEAREST][RARCH_WRAP_DEFAULT];
}