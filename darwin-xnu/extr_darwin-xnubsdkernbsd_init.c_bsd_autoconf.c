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
struct pseudo_init {int /*<<< orphan*/  ps_count; int /*<<< orphan*/  (* ps_func ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  IOKitBSDInit () ; 
 int /*<<< orphan*/  kminit () ; 
 int /*<<< orphan*/  kprintf (char*) ; 
 struct pseudo_init* pseudo_inits ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

kern_return_t
bsd_autoconf(void)
{
	kprintf("bsd_autoconf: calling kminit\n");
	kminit();

	/* 
	 * Early startup for bsd pseudodevices.
	 */
	{
	    struct pseudo_init *pi;
	
	    for (pi = pseudo_inits; pi->ps_func; pi++)
		(*pi->ps_func) (pi->ps_count);
	}

	return( IOKitBSDInit());
}