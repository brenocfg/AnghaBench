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
struct TYPE_3__ {int /*<<< orphan*/ * views; scalar_t__ views_count; } ;
struct TYPE_4__ {int view_index; TYPE_1__ view_array; int /*<<< orphan*/ * view; } ;

/* Variables and functions */
 int MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN (int,scalar_t__) ; 
 TYPE_2__* video_layout_state ; 
 int /*<<< orphan*/  video_layout_view_change () ; 

int video_layout_view_select(int index)
{
   index = MAX(0, MIN(index, video_layout_state->view_array.views_count - 1));

   video_layout_state->view_index = index;
   video_layout_state->view = video_layout_state->view_array.views_count ?
      &video_layout_state->view_array.views[index] : NULL;

   video_layout_view_change();

   return index;
}