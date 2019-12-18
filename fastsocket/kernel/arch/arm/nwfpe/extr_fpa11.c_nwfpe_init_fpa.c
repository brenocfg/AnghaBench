#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  union fp_state {int dummy; } fp_state ;
struct TYPE_3__ {int initflag; } ;
typedef  TYPE_1__ FPA11 ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  resetFPA11 () ; 

void nwfpe_init_fpa(union fp_state *fp)
{
	FPA11 *fpa11 = (FPA11 *)fp;
#ifdef NWFPE_DEBUG
	printk("NWFPE: setting up state.\n");
#endif
 	memset(fpa11, 0, sizeof(FPA11));
	resetFPA11();
	fpa11->initflag = 1;
}