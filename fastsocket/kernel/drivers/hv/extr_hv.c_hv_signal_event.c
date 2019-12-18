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
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  HVCALL_SIGNAL_EVENT ; 
 int do_hypercall (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 

u16 hv_signal_event(void *con_id)
{
	u16 status;

	status = (do_hypercall(HVCALL_SIGNAL_EVENT, con_id, NULL) & 0xFFFF);

	return status;
}