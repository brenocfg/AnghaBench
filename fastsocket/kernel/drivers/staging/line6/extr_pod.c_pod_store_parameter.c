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
struct TYPE_2__ {int* control; } ;
struct usb_line6_pod {int dirty; int /*<<< orphan*/  param_dirty; TYPE_1__ prog_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pod_store_parameter(struct usb_line6_pod *pod, int param, int value)
{
	pod->prog_data.control[param] = value;
	set_bit(param, pod->param_dirty);
	pod->dirty = 1;
}