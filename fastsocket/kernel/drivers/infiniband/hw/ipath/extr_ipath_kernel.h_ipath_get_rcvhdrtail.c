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
typedef  int /*<<< orphan*/  u32 ;
struct ipath_portdata {scalar_t__ port_rcvhdrtail_kvaddr; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/  volatile) ; 

__attribute__((used)) static inline u32 ipath_get_rcvhdrtail(const struct ipath_portdata *pd)
{
	return (u32) le64_to_cpu(*((volatile __le64 *)
				pd->port_rcvhdrtail_kvaddr));
}