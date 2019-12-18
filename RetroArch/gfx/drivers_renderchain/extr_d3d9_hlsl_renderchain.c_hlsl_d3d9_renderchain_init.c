#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_info_t ;
struct LinkInfo {int dummy; } ;
struct TYPE_9__ {int pixel_size; int /*<<< orphan*/  dev; scalar_t__ frame_count; int /*<<< orphan*/ * final_viewport; } ;
struct TYPE_7__ {int /*<<< orphan*/  stock_shader; TYPE_6__ chain; } ;
typedef  TYPE_1__ hlsl_renderchain_t ;
struct TYPE_8__ {scalar_t__ renderchain_data; } ;
typedef  TYPE_2__ d3d9_video_t ;
typedef  int /*<<< orphan*/  LPDIRECT3DDEVICE9 ;
typedef  int /*<<< orphan*/  D3DVIEWPORT9 ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 unsigned int RETRO_PIXEL_FORMAT_RGB565 ; 
 unsigned int RETRO_PIXEL_FORMAT_XRGB8888 ; 
 int /*<<< orphan*/  d3d9_hlsl_bind_program (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3d9_hlsl_load_program (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlsl_d3d9_renderchain_create_first_pass (int /*<<< orphan*/ ,TYPE_6__*,struct LinkInfo const*,unsigned int) ; 
 int /*<<< orphan*/  hlsl_d3d9_renderchain_init_shader (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  stock_hlsl_program ; 

__attribute__((used)) static bool hlsl_d3d9_renderchain_init(
      d3d9_video_t *d3d,
      const video_info_t *video_info,
      LPDIRECT3DDEVICE9 dev,
      const D3DVIEWPORT9 *final_viewport,
      const struct LinkInfo *info,
      bool rgb32
      )
{
   hlsl_renderchain_t *chain     = (hlsl_renderchain_t*)
      d3d->renderchain_data;
   unsigned fmt                       = (rgb32)
      ? RETRO_PIXEL_FORMAT_XRGB8888 : RETRO_PIXEL_FORMAT_RGB565;

   if (!chain)
      return false;
   if (!hlsl_d3d9_renderchain_init_shader(d3d, chain))
   {
      RARCH_ERR("[D3D9 HLSL]: Failed to initialize shader subsystem.\n");
      return false;
   }

   chain->chain.dev                         = dev;
   chain->chain.final_viewport              = (D3DVIEWPORT9*)final_viewport;
   chain->chain.frame_count                 = 0;
   chain->chain.pixel_size                  = (fmt == RETRO_PIXEL_FORMAT_RGB565) ? 2 : 4;

   if (!hlsl_d3d9_renderchain_create_first_pass(dev, &chain->chain, info, fmt))
      return false;
   if (!d3d9_hlsl_load_program(chain->chain.dev, &chain->stock_shader, stock_hlsl_program))
      return false;

   d3d9_hlsl_bind_program(&chain->stock_shader, dev);

   return true;
}