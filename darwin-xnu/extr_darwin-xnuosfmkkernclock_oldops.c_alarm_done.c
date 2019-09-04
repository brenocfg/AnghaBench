#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  spl_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  TYPE_1__* alarm_t ;
struct TYPE_4__ {scalar_t__ al_status; scalar_t__ al_port; struct TYPE_4__* al_next; int /*<<< orphan*/  al_time; int /*<<< orphan*/  al_type; int /*<<< orphan*/  al_port_type; struct TYPE_4__* al_prev; } ;

/* Variables and functions */
 scalar_t__ ALARM_DONE ; 
 scalar_t__ ALARM_FREE ; 
 scalar_t__ IP_NULL ; 
 scalar_t__ IP_VALID (scalar_t__) ; 
 int /*<<< orphan*/  KERN_ABORTED ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  LOCK_ALARM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNLOCK_ALARM (int /*<<< orphan*/ ) ; 
 TYPE_1__* alrmdone ; 
 TYPE_1__* alrmfree ; 
 int /*<<< orphan*/  clock_alarm_reply (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
alarm_done(void)
{
	alarm_t	alrm;
	kern_return_t		code;
	spl_t				s;

	LOCK_ALARM(s);
	while ((alrm = alrmdone) != NULL) {
		if ((alrmdone = alrm->al_next) != NULL)
			alrmdone->al_prev = (alarm_t)&alrmdone;
		UNLOCK_ALARM(s);

		code = (alrm->al_status == ALARM_DONE? KERN_SUCCESS: KERN_ABORTED);
		if (alrm->al_port != IP_NULL) {
			/* Deliver message to designated port */
			if (IP_VALID(alrm->al_port)) {
				clock_alarm_reply(alrm->al_port, alrm->al_port_type, code,
								  				alrm->al_type, alrm->al_time);
			}

			LOCK_ALARM(s);
			alrm->al_status = ALARM_FREE;
			alrm->al_next = alrmfree;
			alrmfree = alrm;
		}
		else
			panic("clock_alarm_deliver");
	}

	UNLOCK_ALARM(s);
}