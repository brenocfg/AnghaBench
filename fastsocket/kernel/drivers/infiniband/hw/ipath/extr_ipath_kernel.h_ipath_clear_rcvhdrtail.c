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
typedef  unsigned long long u64 ;
struct ipath_portdata {scalar_t__ port_rcvhdrtail_kvaddr; } ;

/* Variables and functions */

__attribute__((used)) static inline void ipath_clear_rcvhdrtail(const struct ipath_portdata *pd)
{
	*((u64 *) pd->port_rcvhdrtail_kvaddr) = 0ULL;
}