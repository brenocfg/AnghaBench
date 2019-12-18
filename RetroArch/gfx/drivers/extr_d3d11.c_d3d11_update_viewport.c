#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {float width; float height; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_7__ {float x; float y; float z; float w; } ;
struct TYPE_6__ {float Width; float Height; float MaxDepth; int /*<<< orphan*/  TopLeftY; int /*<<< orphan*/  TopLeftX; } ;
struct TYPE_8__ {TYPE_2__ output_size; TYPE_1__ viewport; } ;
struct TYPE_9__ {int resize_render_targets; int resize_viewport; TYPE_5__ vp; TYPE_3__ frame; scalar_t__ shader_preset; int /*<<< orphan*/  keep_aspect; } ;
typedef  TYPE_4__ d3d11_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  video_driver_update_viewport (TYPE_5__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void d3d11_update_viewport(void* data, bool force_full)
{
   d3d11_video_t* d3d11 = (d3d11_video_t*)data;

   video_driver_update_viewport(&d3d11->vp, force_full, d3d11->keep_aspect);

   d3d11->frame.viewport.TopLeftX = d3d11->vp.x;
   d3d11->frame.viewport.TopLeftY = d3d11->vp.y;
   d3d11->frame.viewport.Width    = d3d11->vp.width;
   d3d11->frame.viewport.Height   = d3d11->vp.height;
   d3d11->frame.viewport.MaxDepth = 0.0f;
   d3d11->frame.viewport.MaxDepth = 1.0f;

   if (d3d11->shader_preset && (d3d11->frame.output_size.x != d3d11->vp.width ||
            d3d11->frame.output_size.y != d3d11->vp.height))
      d3d11->resize_render_targets = true;

   d3d11->frame.output_size.x = d3d11->vp.width;
   d3d11->frame.output_size.y = d3d11->vp.height;
   d3d11->frame.output_size.z = 1.0f / d3d11->vp.width;
   d3d11->frame.output_size.w = 1.0f / d3d11->vp.height;

   d3d11->resize_viewport = false;
}