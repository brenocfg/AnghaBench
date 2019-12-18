#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct xencomm_handle {int dummy; } ;
struct evtchn_op {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int xencomm_arch_hypercall_event_channel_op (int,struct xencomm_handle*) ; 
 struct xencomm_handle* xencomm_map_no_alloc (void*,int) ; 

int
xencomm_hypercall_event_channel_op(int cmd, void *op)
{
	struct xencomm_handle *desc;
	desc = xencomm_map_no_alloc(op, sizeof(struct evtchn_op));
	if (desc == NULL)
		return -EINVAL;

	return xencomm_arch_hypercall_event_channel_op(cmd, desc);
}