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
struct TYPE_2__ {scalar_t__ expires; int /*<<< orphan*/  function; } ;
struct qib_qp {TYPE_1__ s_timer; scalar_t__ timeout_jiffies; int /*<<< orphan*/  s_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  QIB_S_TIMER ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  rc_timeout ; 

__attribute__((used)) static void start_timer(struct qib_qp *qp)
{
	qp->s_flags |= QIB_S_TIMER;
	qp->s_timer.function = rc_timeout;
	/* 4.096 usec. * (1 << qp->timeout) */
	qp->s_timer.expires = jiffies + qp->timeout_jiffies;
	add_timer(&qp->s_timer);
}