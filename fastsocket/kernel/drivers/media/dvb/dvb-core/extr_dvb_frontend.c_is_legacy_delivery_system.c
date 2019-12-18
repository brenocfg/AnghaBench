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
typedef  scalar_t__ fe_delivery_system_t ;

/* Variables and functions */
 scalar_t__ SYS_ATSC ; 
 scalar_t__ SYS_DVBC_ANNEX_AC ; 
 scalar_t__ SYS_DVBC_ANNEX_B ; 
 scalar_t__ SYS_DVBS ; 
 scalar_t__ SYS_DVBT ; 
 scalar_t__ SYS_UNDEFINED ; 

__attribute__((used)) static int is_legacy_delivery_system(fe_delivery_system_t s)
{
	if((s == SYS_UNDEFINED) || (s == SYS_DVBC_ANNEX_AC) ||
	   (s == SYS_DVBC_ANNEX_B) || (s == SYS_DVBT) || (s == SYS_DVBS) ||
	   (s == SYS_ATSC))
		return 1;

	return 0;
}