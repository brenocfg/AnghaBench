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
struct ip_vs_estimator {scalar_t__ outbps; scalar_t__ inbps; scalar_t__ outpps; scalar_t__ inpps; scalar_t__ cps; scalar_t__ last_outpkts; scalar_t__ last_inpkts; scalar_t__ last_conns; scalar_t__ last_outbytes; scalar_t__ last_inbytes; } ;
struct ip_vs_stats {struct ip_vs_estimator est; } ;

/* Variables and functions */

void ip_vs_zero_estimator(struct ip_vs_stats *stats)
{
	struct ip_vs_estimator *est = &stats->est;

	/* set counters zero, caller must hold the stats->lock lock */
	est->last_inbytes = 0;
	est->last_outbytes = 0;
	est->last_conns = 0;
	est->last_inpkts = 0;
	est->last_outpkts = 0;
	est->cps = 0;
	est->inpps = 0;
	est->outpps = 0;
	est->inbps = 0;
	est->outbps = 0;
}