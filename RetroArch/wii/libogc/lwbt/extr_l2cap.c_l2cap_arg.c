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
struct l2cap_pcb {void* callback_arg; } ;

/* Variables and functions */

void l2cap_arg(struct l2cap_pcb *pcb, void *arg)
{
	pcb->callback_arg = arg;
}