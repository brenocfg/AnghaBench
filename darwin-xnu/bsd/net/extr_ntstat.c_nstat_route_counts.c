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
struct rtentry {int rt_flags; struct nstat_counts* rt_stats; } ;
struct nstat_counts {scalar_t__ nstat_cell_txbytes; scalar_t__ nstat_cell_rxbytes; int /*<<< orphan*/  nstat_var_rtt; int /*<<< orphan*/  nstat_avg_rtt; int /*<<< orphan*/  nstat_min_rtt; int /*<<< orphan*/  nstat_connectsuccesses; int /*<<< orphan*/  nstat_connectattempts; int /*<<< orphan*/  nstat_txretransmit; int /*<<< orphan*/  nstat_rxoutoforderbytes; int /*<<< orphan*/  nstat_rxduplicatebytes; int /*<<< orphan*/  nstat_txbytes; int /*<<< orphan*/  nstat_txpackets; int /*<<< orphan*/  nstat_rxbytes; int /*<<< orphan*/  nstat_rxpackets; } ;
typedef  scalar_t__ nstat_provider_cookie_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int RTF_UP ; 
 int /*<<< orphan*/  atomic_get_64 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (struct nstat_counts*,int) ; 

__attribute__((used)) static errno_t
nstat_route_counts(
	nstat_provider_cookie_t	cookie,
	struct nstat_counts		*out_counts,
	int						*out_gone)
{
	struct rtentry		*rt = (struct rtentry*)cookie;
	struct nstat_counts	*rt_stats = rt->rt_stats;

	if (out_gone) *out_gone = 0;

	if (out_gone && (rt->rt_flags & RTF_UP) == 0) *out_gone = 1;

	if (rt_stats)
	{
		atomic_get_64(out_counts->nstat_rxpackets, &rt_stats->nstat_rxpackets);
		atomic_get_64(out_counts->nstat_rxbytes, &rt_stats->nstat_rxbytes);
		atomic_get_64(out_counts->nstat_txpackets, &rt_stats->nstat_txpackets);
		atomic_get_64(out_counts->nstat_txbytes, &rt_stats->nstat_txbytes);
		out_counts->nstat_rxduplicatebytes = rt_stats->nstat_rxduplicatebytes;
		out_counts->nstat_rxoutoforderbytes = rt_stats->nstat_rxoutoforderbytes;
		out_counts->nstat_txretransmit = rt_stats->nstat_txretransmit;
		out_counts->nstat_connectattempts = rt_stats->nstat_connectattempts;
		out_counts->nstat_connectsuccesses = rt_stats->nstat_connectsuccesses;
		out_counts->nstat_min_rtt = rt_stats->nstat_min_rtt;
		out_counts->nstat_avg_rtt = rt_stats->nstat_avg_rtt;
		out_counts->nstat_var_rtt = rt_stats->nstat_var_rtt;
		out_counts->nstat_cell_rxbytes = out_counts->nstat_cell_txbytes = 0;
	}
	else
	{
		bzero(out_counts, sizeof(*out_counts));
	}

	return 0;
}