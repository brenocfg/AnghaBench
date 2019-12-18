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
struct snmpd_usmstat {int dummy; } ;

/* Variables and functions */
 struct snmpd_usmstat snmpd_usmstats ; 

struct snmpd_usmstat *
bsnmpd_get_usm_stats(void)
{
	return (&snmpd_usmstats);
}