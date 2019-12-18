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
struct TYPE_2__ {scalar_t__ dqb_rsvspace; int /*<<< orphan*/  dqb_curspace; } ;
struct dquot {TYPE_1__ dq_dqb; } ;
typedef  scalar_t__ qsize_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

__attribute__((used)) static void dquot_claim_reserved_space(struct dquot *dquot, qsize_t number)
{
	if (dquot->dq_dqb.dqb_rsvspace < number) {
		WARN_ON_ONCE(1);
		number = dquot->dq_dqb.dqb_rsvspace;
	}
	dquot->dq_dqb.dqb_curspace += number;
	dquot->dq_dqb.dqb_rsvspace -= number;
}