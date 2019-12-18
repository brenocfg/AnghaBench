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
typedef  int u16 ;
struct brcms_hardware {int /*<<< orphan*/  d11core; TYPE_1__* band; } ;
struct TYPE_2__ {int CWmin; } ;

/* Variables and functions */
 int /*<<< orphan*/  D11REGOFFS (int /*<<< orphan*/ ) ; 
 int OBJADDR_SCR_SEL ; 
 int S_DOT11_CWMIN ; 
 int /*<<< orphan*/  bcma_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  objaddr ; 
 int /*<<< orphan*/  objdata ; 

__attribute__((used)) static void brcms_b_set_cwmin(struct brcms_hardware *wlc_hw, u16 newmin)
{
	wlc_hw->band->CWmin = newmin;

	bcma_write32(wlc_hw->d11core, D11REGOFFS(objaddr),
		     OBJADDR_SCR_SEL | S_DOT11_CWMIN);
	(void)bcma_read32(wlc_hw->d11core, D11REGOFFS(objaddr));
	bcma_write32(wlc_hw->d11core, D11REGOFFS(objdata), newmin);
}