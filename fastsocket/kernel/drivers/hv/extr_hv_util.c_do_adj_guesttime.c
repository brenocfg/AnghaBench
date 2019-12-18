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
typedef  int u64 ;
struct timespec {int dummy; } ;
typedef  int s64 ;

/* Variables and functions */
 int WLTIMEDELTA ; 
 int /*<<< orphan*/  do_settimeofday (struct timespec*) ; 
 struct timespec ns_to_timespec (int) ; 

__attribute__((used)) static inline void do_adj_guesttime(u64 hosttime)
{
	s64 host_tns;
	struct timespec host_ts;

	host_tns = (hosttime - WLTIMEDELTA) * 100;
	host_ts = ns_to_timespec(host_tns);

	do_settimeofday(&host_ts);
}