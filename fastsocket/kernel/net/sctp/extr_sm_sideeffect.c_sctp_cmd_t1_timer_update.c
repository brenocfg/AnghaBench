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
struct sctp_transport {scalar_t__ init_sent_count; } ;
struct sctp_association {scalar_t__ init_cycle; int* timeouts; int max_init_timeo; int /*<<< orphan*/  init_err_counter; struct sctp_transport* init_last_sent_to; } ;
typedef  size_t sctp_event_timeout_t ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_DEBUG_PRINTK (char*,char*,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void sctp_cmd_t1_timer_update(struct sctp_association *asoc,
				    sctp_event_timeout_t timer,
				    char *name)
{
	struct sctp_transport *t;

	t = asoc->init_last_sent_to;
	asoc->init_err_counter++;

	if (t->init_sent_count > (asoc->init_cycle + 1)) {
		asoc->timeouts[timer] *= 2;
		if (asoc->timeouts[timer] > asoc->max_init_timeo) {
			asoc->timeouts[timer] = asoc->max_init_timeo;
		}
		asoc->init_cycle++;
		SCTP_DEBUG_PRINTK(
			"T1 %s Timeout adjustment"
			" init_err_counter: %d"
			" cycle: %d"
			" timeout: %ld\n",
			name,
			asoc->init_err_counter,
			asoc->init_cycle,
			asoc->timeouts[timer]);
	}

}