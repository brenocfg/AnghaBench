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
 scalar_t__ dccp_statistics ; 
 int /*<<< orphan*/  snmp_mib_free (void**) ; 

__attribute__((used)) static inline void dccp_mib_exit(void)
{
	snmp_mib_free((void**)dccp_statistics);
}