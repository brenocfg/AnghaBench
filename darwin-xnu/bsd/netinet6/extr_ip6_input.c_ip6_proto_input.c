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
struct timeval {int dummy; } ;
typedef  int /*<<< orphan*/  protocol_family_t ;
typedef  int /*<<< orphan*/  mbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ip6_input (int /*<<< orphan*/ ) ; 
 scalar_t__ ip6_input_measure ; 
 int /*<<< orphan*/  net_perf ; 
 int /*<<< orphan*/  net_perf_histogram (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  net_perf_measure_time (int /*<<< orphan*/ *,struct timeval*,int) ; 
 int /*<<< orphan*/  net_perf_start_time (int /*<<< orphan*/ *,struct timeval*) ; 

__attribute__((used)) static void
ip6_proto_input(protocol_family_t protocol, mbuf_t packet)
{
#pragma unused(protocol)
#if INET
	struct timeval start_tv;
	if (ip6_input_measure)
		net_perf_start_time(&net_perf, &start_tv);
#endif /* INET */
	ip6_input(packet);
#if INET
	if (ip6_input_measure) {
		net_perf_measure_time(&net_perf, &start_tv, 1);
		net_perf_histogram(&net_perf, 1);
	}
#endif /* INET */
}