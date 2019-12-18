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
typedef  int u32 ;
struct u132 {int hc_fminterval; } ;

/* Variables and functions */
 int FIT ; 
 int periodicstart ; 
 int u132_read_pcimem (struct u132*,int,int*) ; 
 int u132_write_pcimem (struct u132*,int,int) ; 

__attribute__((used)) static int u132_periodic_reinit(struct u132 *u132)
{
	int retval;
	u32 fi = u132->hc_fminterval & 0x03fff;
	u32 fit;
	u32 fminterval;
	retval = u132_read_pcimem(u132, fminterval, &fminterval);
	if (retval)
		return retval;
	fit = fminterval & FIT;
	retval = u132_write_pcimem(u132, fminterval,
		(fit ^ FIT) | u132->hc_fminterval);
	if (retval)
		return retval;
	retval = u132_write_pcimem(u132, periodicstart,
		((9 * fi) / 10) & 0x3fff);
	if (retval)
		return retval;
	return 0;
}