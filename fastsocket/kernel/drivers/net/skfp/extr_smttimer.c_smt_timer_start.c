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
typedef  int u_long ;
struct smt_timer {int tm_token; int tm_delta; struct smt_timer* tm_next; int /*<<< orphan*/  tm_active; struct s_smc* tm_smc; } ;
struct TYPE_2__ {struct smt_timer* st_queue; } ;
struct s_smc {TYPE_1__ t; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  hwt_start (struct s_smc*,int) ; 
 int /*<<< orphan*/  smt_timer_stop (struct s_smc*,struct smt_timer*) ; 
 int /*<<< orphan*/  timer_done (struct s_smc*,int /*<<< orphan*/ ) ; 

void smt_timer_start(struct s_smc *smc, struct smt_timer *timer, u_long time,
		     u_long token)
{
	struct smt_timer	**prev ;
	struct smt_timer	*tm ;
	u_long			delta = 0 ;

	time /= 16 ;		/* input is uS, clock ticks are 16uS */
	if (!time)
		time = 1 ;
	smt_timer_stop(smc,timer) ;
	timer->tm_smc = smc ;
	timer->tm_token = token ;
	timer->tm_active = TRUE ;
	if (!smc->t.st_queue) {
		smc->t.st_queue = timer ;
		timer->tm_next = NULL;
		timer->tm_delta = time ;
		hwt_start(smc,time) ;
		return ;
	}
	/*
	 * timer correction
	 */
	timer_done(smc,0) ;

	/*
	 * find position in queue
	 */
	delta = 0 ;
	for (prev = &smc->t.st_queue ; (tm = *prev) ; prev = &tm->tm_next ) {
		if (delta + tm->tm_delta > time) {
			break ;
		}
		delta += tm->tm_delta ;
	}
	/* insert in queue */
	*prev = timer ;
	timer->tm_next = tm ;
	timer->tm_delta = time - delta ;
	if (tm)
		tm->tm_delta -= timer->tm_delta ;
	/*
	 * start new with first
	 */
	hwt_start(smc,smc->t.st_queue->tm_delta) ;
}