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
struct dccp_mib {int dummy; } ;

/* Variables and functions */
 scalar_t__ dccp_statistics ; 
 int snmp_mib_init (void**,int) ; 

__attribute__((used)) static inline int dccp_mib_init(void)
{
	return snmp_mib_init((void**)dccp_statistics, sizeof(struct dccp_mib));
}