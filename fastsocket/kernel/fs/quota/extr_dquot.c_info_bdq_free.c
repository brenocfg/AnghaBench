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
struct TYPE_2__ {scalar_t__ dqb_curspace; scalar_t__ dqb_bsoftlimit; scalar_t__ dqb_bhardlimit; } ;
struct dquot {TYPE_1__ dq_dqb; int /*<<< orphan*/  dq_flags; } ;
typedef  scalar_t__ qsize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DQ_FAKE_B ; 
 int QUOTA_NL_BHARDBELOW ; 
 int QUOTA_NL_BSOFTBELOW ; 
 int QUOTA_NL_NOWARN ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int info_bdq_free(struct dquot *dquot, qsize_t space)
{
	if (test_bit(DQ_FAKE_B, &dquot->dq_flags) ||
	    dquot->dq_dqb.dqb_curspace <= dquot->dq_dqb.dqb_bsoftlimit)
		return QUOTA_NL_NOWARN;

	if (dquot->dq_dqb.dqb_curspace - space <= dquot->dq_dqb.dqb_bsoftlimit)
		return QUOTA_NL_BSOFTBELOW;
	if (dquot->dq_dqb.dqb_curspace >= dquot->dq_dqb.dqb_bhardlimit &&
	    dquot->dq_dqb.dqb_curspace - space < dquot->dq_dqb.dqb_bhardlimit)
		return QUOTA_NL_BHARDBELOW;
	return QUOTA_NL_NOWARN;
}