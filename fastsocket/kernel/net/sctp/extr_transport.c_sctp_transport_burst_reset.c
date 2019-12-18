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
struct sctp_transport {scalar_t__ burst_limited; scalar_t__ cwnd; } ;

/* Variables and functions */

void sctp_transport_burst_reset(struct sctp_transport *t)
{
	if (t->burst_limited) {
		t->cwnd = t->burst_limited;
		t->burst_limited = 0;
	}
}