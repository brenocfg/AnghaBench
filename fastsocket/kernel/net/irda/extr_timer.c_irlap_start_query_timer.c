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
struct irlap_cb {int /*<<< orphan*/  query_timer; } ;

/* Variables and functions */
 int HZ ; 
 int SMALLBUSY_TIMEOUT ; 
 int XIDEXTRA_TIMEOUT ; 
 int /*<<< orphan*/  irda_start_timer (int /*<<< orphan*/ *,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irlap_query_timer_expired ; 
 int sysctl_slot_timeout ; 

void irlap_start_query_timer(struct irlap_cb *self, int S, int s)
{
	int timeout;

	/* Calculate when the peer discovery should end. Normally, we
	 * get the end-of-discovery frame, so this is just in case
	 * we miss it.
	 * Basically, we multiply the number of remaining slots by our
	 * slot time, plus add some extra time to properly receive the last
	 * discovery packet (which is longer due to extra discovery info),
	 * to avoid messing with for incomming connections requests and
	 * to accomodate devices that perform discovery slower than us.
	 * Jean II */
	timeout = ((sysctl_slot_timeout * HZ / 1000) * (S - s)
		   + XIDEXTRA_TIMEOUT + SMALLBUSY_TIMEOUT);

	/* Set or re-set the timer. We reset the timer for each received
	 * discovery query, which allow us to automatically adjust to
	 * the speed of the peer discovery (faster or slower). Jean II */
	irda_start_timer( &self->query_timer, timeout, (void *) self,
			  irlap_query_timer_expired);
}