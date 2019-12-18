#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* views; } ;
struct TYPE_6__ {TYPE_2__ view_array; } ;
struct TYPE_4__ {char const* name; } ;

/* Variables and functions */
 TYPE_3__* video_layout_state ; 

const char *video_layout_view_name(int index)
{
   return video_layout_state->view_array.views[index].name;
}