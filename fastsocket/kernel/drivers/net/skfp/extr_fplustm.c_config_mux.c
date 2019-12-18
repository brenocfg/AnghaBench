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
 int /*<<< orphan*/  FM_A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_MDREG1 ; 
 int /*<<< orphan*/  FM_SELRA ; 
 int /*<<< orphan*/  SETMASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plc_config_mux (struct s_smc*,int) ; 

void config_mux(struct s_smc *smc, int mux)
{
	plc_config_mux(smc,mux) ;

	SETMASK(FM_A(FM_MDREG1),FM_SELRA,FM_SELRA) ;
}