#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_layout_bounds_t ;
struct TYPE_4__ {TYPE_1__* view; } ;
struct TYPE_3__ {int /*<<< orphan*/  const* screens; } ;

/* Variables and functions */
 TYPE_2__* video_layout_state ; 

const video_layout_bounds_t *video_layout_screen(int index)
{
   return &video_layout_state->view->screens[index];
}