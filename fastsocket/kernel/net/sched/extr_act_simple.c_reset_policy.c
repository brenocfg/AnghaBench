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
struct tcf_defact {int /*<<< orphan*/  tcf_lock; int /*<<< orphan*/  tcfd_defdata; int /*<<< orphan*/  tcf_action; } ;
struct tc_defact {int /*<<< orphan*/  action; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIMP_MAX_DATA ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void reset_policy(struct tcf_defact *d, char *defdata,
			 struct tc_defact *p)
{
	spin_lock_bh(&d->tcf_lock);
	d->tcf_action = p->action;
	memset(d->tcfd_defdata, 0, SIMP_MAX_DATA);
	strlcpy(d->tcfd_defdata, defdata, SIMP_MAX_DATA);
	spin_unlock_bh(&d->tcf_lock);
}