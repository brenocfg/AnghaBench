#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  chain; } ;
typedef  TYPE_1__ hlsl_renderchain_t ;
typedef  int /*<<< orphan*/  d3d9_video_t ;
struct TYPE_5__ {int /*<<< orphan*/  dev; int /*<<< orphan*/ * final_viewport; } ;
typedef  TYPE_2__ d3d9_renderchain_t ;
typedef  int /*<<< orphan*/  D3DVIEWPORT9 ;

/* Variables and functions */
 int /*<<< orphan*/  d3d9_recompute_pass_sizes (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hlsl_d3d9_renderchain_set_final_viewport(
      d3d9_video_t *d3d,
      void *renderchain_data,
      const D3DVIEWPORT9 *final_viewport)
{
   hlsl_renderchain_t      *_chain = (hlsl_renderchain_t*)renderchain_data;
   d3d9_renderchain_t      *chain  = (d3d9_renderchain_t*)&_chain->chain;

   if (chain && final_viewport)
      chain->final_viewport = (D3DVIEWPORT9*)final_viewport;

   d3d9_recompute_pass_sizes(chain->dev, chain, d3d);
}