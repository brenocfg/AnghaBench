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
struct cyclades_port {int x_break; int /*<<< orphan*/  xmit_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  start_xmit (struct cyclades_port*) ; 

__attribute__((used)) static void send_break(struct cyclades_port *info, int duration)
{				/* Let the transmit ISR take care of this (since it
				   requires stuffing characters into the output stream).
				 */
	info->x_break = duration;
	if (!info->xmit_cnt) {
		start_xmit(info);
	}
}