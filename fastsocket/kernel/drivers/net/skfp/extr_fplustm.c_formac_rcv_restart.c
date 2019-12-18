#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  rx_mode; } ;
struct TYPE_4__ {TYPE_1__ fp; } ;
struct s_smc {TYPE_2__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_ADDRX ; 
 int /*<<< orphan*/  FM_CMDREG1 ; 
 int /*<<< orphan*/  FM_ICLLR ; 
 int /*<<< orphan*/  FM_MDREG1 ; 
 int /*<<< orphan*/  SETMASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outpw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void formac_rcv_restart(struct s_smc *smc)
{
	/* enable receive function */
	SETMASK(FM_A(FM_MDREG1),smc->hw.fp.rx_mode,FM_ADDRX) ;

	outpw(FM_A(FM_CMDREG1),FM_ICLLR) ;	/* clear receive lock */
}