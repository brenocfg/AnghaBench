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
struct s_smc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SK_UNUSED (struct s_smc*) ; 

void init_plc(struct s_smc *smc)
{
	SK_UNUSED(smc) ;

	/*
	 * dummy
	 * this is an obsolete public entry point that has to remain
	 * for compat. It is used by various drivers.
	 * the work is now done in real_init_plc()
	 * which is called from pcm_init() ;
	 */
}