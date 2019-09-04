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

/* Variables and functions */
 int /*<<< orphan*/  mbuf_report_peak_usage () ; 
 int /*<<< orphan*/  nstat_ifnet_report_ecn_stats () ; 
 int /*<<< orphan*/  nstat_ifnet_report_lim_stats () ; 
 int /*<<< orphan*/  nstat_net_api_report_stats () ; 
 int /*<<< orphan*/  tcp_report_stats () ; 

__attribute__((used)) static void
nstat_sysinfo_generate_report(void)
{
	mbuf_report_peak_usage();
	tcp_report_stats();
	nstat_ifnet_report_ecn_stats();
	nstat_ifnet_report_lim_stats();
	nstat_net_api_report_stats();
}