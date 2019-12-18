#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t titan_which_layer; int /*<<< orphan*/  titan_shadow_type; int /*<<< orphan*/  titan_shadow_enabled; } ;
typedef  TYPE_2__ vdp2draw_struct ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int s32 ;
struct TYPE_7__ {int vdp2width; TYPE_1__** vdp2framebuffer; } ;
struct TYPE_5__ {int priority; int linescreen; int /*<<< orphan*/  shadow_type; int /*<<< orphan*/  shadow_enabled; int /*<<< orphan*/  pixel; } ;

/* Variables and functions */
 TYPE_3__ tt_context ; 

void TitanPutPixel(int priority, s32 x, s32 y, u32 color, int linescreen, vdp2draw_struct* info)
{
   if (priority == 0) return;

   {
      int pos = (y * tt_context.vdp2width) + x;
      tt_context.vdp2framebuffer[info->titan_which_layer][pos].pixel = color;
      tt_context.vdp2framebuffer[info->titan_which_layer][pos].priority = priority;
      tt_context.vdp2framebuffer[info->titan_which_layer][pos].linescreen = linescreen;
      tt_context.vdp2framebuffer[info->titan_which_layer][pos].shadow_enabled = info->titan_shadow_enabled;
      tt_context.vdp2framebuffer[info->titan_which_layer][pos].shadow_type = info->titan_shadow_type;
   }
}