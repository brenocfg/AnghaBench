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
struct mem_dqblk {int /*<<< orphan*/  dqb_itime; int /*<<< orphan*/  dqb_btime; int /*<<< orphan*/  dqb_curinodes; int /*<<< orphan*/  dqb_isoftlimit; int /*<<< orphan*/  dqb_ihardlimit; scalar_t__ dqb_rsvspace; scalar_t__ dqb_curspace; int /*<<< orphan*/  dqb_bsoftlimit; int /*<<< orphan*/  dqb_bhardlimit; } ;
struct if_dqblk {int /*<<< orphan*/  dqb_valid; int /*<<< orphan*/  dqb_itime; int /*<<< orphan*/  dqb_btime; int /*<<< orphan*/  dqb_curinodes; int /*<<< orphan*/  dqb_isoftlimit; int /*<<< orphan*/  dqb_ihardlimit; scalar_t__ dqb_curspace; void* dqb_bsoftlimit; void* dqb_bhardlimit; } ;
struct dquot {struct mem_dqblk dq_dqb; } ;

/* Variables and functions */
 int /*<<< orphan*/  QIF_ALL ; 
 int /*<<< orphan*/  dq_data_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 void* stoqb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_get_dqblk(struct dquot *dquot, struct if_dqblk *di)
{
	struct mem_dqblk *dm = &dquot->dq_dqb;

	spin_lock(&dq_data_lock);
	di->dqb_bhardlimit = stoqb(dm->dqb_bhardlimit);
	di->dqb_bsoftlimit = stoqb(dm->dqb_bsoftlimit);
	di->dqb_curspace = dm->dqb_curspace + dm->dqb_rsvspace;
	di->dqb_ihardlimit = dm->dqb_ihardlimit;
	di->dqb_isoftlimit = dm->dqb_isoftlimit;
	di->dqb_curinodes = dm->dqb_curinodes;
	di->dqb_btime = dm->dqb_btime;
	di->dqb_itime = dm->dqb_itime;
	di->dqb_valid = QIF_ALL;
	spin_unlock(&dq_data_lock);
}