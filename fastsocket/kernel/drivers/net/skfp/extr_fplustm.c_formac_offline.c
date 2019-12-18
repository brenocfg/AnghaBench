#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  hw_state; int /*<<< orphan*/  mac_ring_is_up; } ;
struct s_smc {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FM_A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_ADDET ; 
 int /*<<< orphan*/  FM_CMDREG2 ; 
 int /*<<< orphan*/  FM_IACTR ; 
 int /*<<< orphan*/  FM_MDISRCV ; 
 int /*<<< orphan*/  FM_MDREG1 ; 
 int /*<<< orphan*/  FM_MINIT ; 
 int /*<<< orphan*/  FM_MMODE ; 
 int /*<<< orphan*/  SETMASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STOPPED ; 
 int /*<<< orphan*/  disable_formac (struct s_smc*) ; 
 int /*<<< orphan*/  outpw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void formac_offline(struct s_smc *smc)
{
	outpw(FM_A(FM_CMDREG2),FM_IACTR) ;/* abort current transmit activity */

	/* disable receive function */
	SETMASK(FM_A(FM_MDREG1),FM_MDISRCV,FM_ADDET) ;

	/* FORMAC+ 'Initialize Mode' */
	SETMASK(FM_A(FM_MDREG1),FM_MINIT,FM_MMODE) ;

	disable_formac(smc) ;
	smc->hw.mac_ring_is_up = FALSE ;
	smc->hw.hw_state = STOPPED ;
}