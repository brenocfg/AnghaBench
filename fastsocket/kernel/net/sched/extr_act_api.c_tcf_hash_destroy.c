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
struct tcf_hashinfo {int /*<<< orphan*/  lock; struct tcf_common** htab; int /*<<< orphan*/  hmask; } ;
struct tcf_common {int /*<<< orphan*/  tcfc_rate_est; int /*<<< orphan*/  tcfc_bstats; struct tcf_common* tcfc_next; int /*<<< orphan*/  tcfc_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  gen_kill_estimator (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct tcf_common*) ; 
 unsigned int tcf_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ ) ; 

void tcf_hash_destroy(struct tcf_common *p, struct tcf_hashinfo *hinfo)
{
	unsigned int h = tcf_hash(p->tcfc_index, hinfo->hmask);
	struct tcf_common **p1p;

	for (p1p = &hinfo->htab[h]; *p1p; p1p = &(*p1p)->tcfc_next) {
		if (*p1p == p) {
			write_lock_bh(hinfo->lock);
			*p1p = p->tcfc_next;
			write_unlock_bh(hinfo->lock);
			gen_kill_estimator(&p->tcfc_bstats,
					   &p->tcfc_rate_est);
			kfree(p);
			return;
		}
	}
	WARN_ON(1);
}