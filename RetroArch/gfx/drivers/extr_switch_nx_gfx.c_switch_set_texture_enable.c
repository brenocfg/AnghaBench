#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int enable; int fullscreen; } ;
struct TYPE_7__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_6__ {int /*<<< orphan*/  full_height; int /*<<< orphan*/  full_width; } ;
struct TYPE_9__ {TYPE_3__ menu_texture; TYPE_2__ hw_scale; int /*<<< orphan*/  win; scalar_t__ smooth; TYPE_1__ vp; } ;
typedef  TYPE_4__ switch_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  clear_screen (TYPE_4__*) ; 
 int /*<<< orphan*/  nwindowSetDimensions (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void switch_set_texture_enable(void *data, bool enable, bool full_screen)
{
    switch_video_t *sw = data;
    if (!sw->menu_texture.enable && enable)
        nwindowSetDimensions(sw->win, sw->vp.full_width, sw->vp.full_height);
    else if (!enable && sw->menu_texture.enable && sw->smooth)
    {
        clear_screen(sw);
        nwindowSetDimensions(sw->win, sw->hw_scale.width, sw->hw_scale.height);
    }
    sw->menu_texture.enable = enable;
    sw->menu_texture.fullscreen = full_screen;
}