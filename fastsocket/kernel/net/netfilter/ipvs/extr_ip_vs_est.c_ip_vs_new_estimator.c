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
struct TYPE_2__ {int cps; int inpps; int outpps; int inbps; int outbps; int /*<<< orphan*/  outbytes; int /*<<< orphan*/  inbytes; int /*<<< orphan*/  outpkts; int /*<<< orphan*/  inpkts; int /*<<< orphan*/  conns; } ;
struct ip_vs_estimator {int cps; int inpps; int outpps; int inbps; int outbps; int /*<<< orphan*/  list; int /*<<< orphan*/  last_outbytes; int /*<<< orphan*/  last_inbytes; int /*<<< orphan*/  last_outpkts; int /*<<< orphan*/  last_inpkts; int /*<<< orphan*/  last_conns; } ;
struct ip_vs_stats {TYPE_1__ ustats; struct ip_vs_estimator est; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  est_list ; 
 int /*<<< orphan*/  est_lock ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void ip_vs_new_estimator(struct ip_vs_stats *stats)
{
	struct ip_vs_estimator *est = &stats->est;

	INIT_LIST_HEAD(&est->list);

	est->last_conns = stats->ustats.conns;
	est->cps = stats->ustats.cps<<10;

	est->last_inpkts = stats->ustats.inpkts;
	est->inpps = stats->ustats.inpps<<10;

	est->last_outpkts = stats->ustats.outpkts;
	est->outpps = stats->ustats.outpps<<10;

	est->last_inbytes = stats->ustats.inbytes;
	est->inbps = stats->ustats.inbps<<5;

	est->last_outbytes = stats->ustats.outbytes;
	est->outbps = stats->ustats.outbps<<5;

	spin_lock_bh(&est_lock);
	list_add(&est->list, &est_list);
	spin_unlock_bh(&est_lock);
}