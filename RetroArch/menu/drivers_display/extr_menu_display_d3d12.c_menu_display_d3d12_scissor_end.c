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
struct TYPE_8__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ userdata; } ;
typedef  TYPE_2__ video_frame_info_t ;
struct TYPE_7__ {int /*<<< orphan*/  cmd; } ;
struct TYPE_9__ {TYPE_1__ queue; } ;
typedef  TYPE_3__ d3d12_video_t ;
struct TYPE_10__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; scalar_t__ top; scalar_t__ left; } ;
typedef  TYPE_4__ D3D12_RECT ;

/* Variables and functions */
 int /*<<< orphan*/  D3D12RSSetScissorRects (int /*<<< orphan*/ ,int,TYPE_4__*) ; 

void menu_display_d3d12_scissor_end(video_frame_info_t *video_info)
{
   D3D12_RECT rect;
   d3d12_video_t *d3d12 = (d3d12_video_t*)video_info->userdata;

   if (!d3d12)
      return;

   rect.left            = 0;
   rect.top             = 0;
   rect.right           = video_info->width;
   rect.bottom          = video_info->height;

   D3D12RSSetScissorRects(d3d12->queue.cmd, 1, &rect);
}