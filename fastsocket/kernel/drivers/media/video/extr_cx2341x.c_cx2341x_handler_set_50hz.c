#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cx2341x_handler {int is_50hz; TYPE_1__* video_gop_size; } ;
struct TYPE_2__ {int default_value; } ;

/* Variables and functions */

void cx2341x_handler_set_50hz(struct cx2341x_handler *cxhdl, int is_50hz)
{
	cxhdl->is_50hz = is_50hz;
	cxhdl->video_gop_size->default_value = cxhdl->is_50hz ? 12 : 15;
}