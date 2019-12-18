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
struct sctp_mib {int dummy; } ;

/* Variables and functions */
 scalar_t__ sctp_statistics ; 
 int snmp_mib_init (void**,int) ; 

__attribute__((used)) static inline int init_sctp_mibs(void)
{
	return snmp_mib_init((void**)sctp_statistics, sizeof(struct sctp_mib));
}