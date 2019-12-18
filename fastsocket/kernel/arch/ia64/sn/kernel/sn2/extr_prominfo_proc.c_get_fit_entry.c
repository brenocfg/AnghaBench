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
 int ia64_sn_get_fit_compt (unsigned long,int,unsigned long*,char*,int) ; 

__attribute__((used)) static int
get_fit_entry(unsigned long nasid, int index, unsigned long *fentry,
	      char *banner, int banlen)
{
	return ia64_sn_get_fit_compt(nasid, index, fentry, banner, banlen);
}