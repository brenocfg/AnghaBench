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
struct sctp_transport {unsigned long rto; scalar_t__ state; scalar_t__ hbinterval; } ;

/* Variables and functions */
 scalar_t__ SCTP_PF ; 
 scalar_t__ SCTP_UNCONFIRMED ; 
 scalar_t__ jiffies ; 
 unsigned long sctp_jitter (unsigned long) ; 

unsigned long sctp_transport_timeout(struct sctp_transport *t)
{
	unsigned long timeout;
	timeout = t->rto + sctp_jitter(t->rto);
	if ((t->state != SCTP_UNCONFIRMED) &&
	    (t->state != SCTP_PF))
		timeout += t->hbinterval;
	timeout += jiffies;
	return timeout;
}