#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {float width; float height; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_9__ {float x; float y; float z; float w; } ;
struct TYPE_8__ {scalar_t__ bottom; scalar_t__ right; scalar_t__ left; scalar_t__ top; } ;
struct TYPE_7__ {float Width; float Height; float MaxDepth; scalar_t__ TopLeftY; scalar_t__ TopLeftX; } ;
struct TYPE_10__ {TYPE_3__ output_size; TYPE_2__ scissorRect; TYPE_1__ viewport; } ;
struct TYPE_11__ {int resize_render_targets; int resize_viewport; TYPE_6__ vp; TYPE_4__ frame; scalar_t__ shader_preset; int /*<<< orphan*/  keep_aspect; } ;
typedef  TYPE_5__ d3d12_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  video_driver_update_viewport (TYPE_6__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void d3d12_update_viewport(void* data, bool force_full)
{
   d3d12_video_t* d3d12 = (d3d12_video_t*)data;

   video_driver_update_viewport(&d3d12->vp, force_full, d3d12->keep_aspect);

   d3d12->frame.viewport.TopLeftX = d3d12->vp.x;
   d3d12->frame.viewport.TopLeftY = d3d12->vp.y;
   d3d12->frame.viewport.Width    = d3d12->vp.width;
   d3d12->frame.viewport.Height   = d3d12->vp.height;
   d3d12->frame.viewport.MaxDepth = 0.0f;
   d3d12->frame.viewport.MaxDepth = 1.0f;

   /* having to add vp.x and vp.y here doesn't make any sense */
   d3d12->frame.scissorRect.top    = 0;
   d3d12->frame.scissorRect.left   = 0;
   d3d12->frame.scissorRect.right  = d3d12->vp.x + d3d12->vp.width;
   d3d12->frame.scissorRect.bottom = d3d12->vp.y + d3d12->vp.height;

   if (d3d12->shader_preset && (d3d12->frame.output_size.x != d3d12->vp.width ||
                                d3d12->frame.output_size.y != d3d12->vp.height))
      d3d12->resize_render_targets = true;

   d3d12->frame.output_size.x = d3d12->vp.width;
   d3d12->frame.output_size.y = d3d12->vp.height;
   d3d12->frame.output_size.z = 1.0f / d3d12->vp.width;
   d3d12->frame.output_size.w = 1.0f / d3d12->vp.height;

   d3d12->resize_viewport = false;
}