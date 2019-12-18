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
typedef  int uint ;
struct TYPE_4__ {TYPE_1__* brgc; } ;
struct TYPE_3__ {int /*<<< orphan*/  l; } ;

/* Variables and functions */
 int BRG_UART_CLK ; 
 int CPM_BRG_EN ; 
 TYPE_2__* pquicc ; 

void
m360_cpm_setbrg(uint brg, uint rate)
{
	volatile uint	*bp;

	/* This is good enough to get SMCs running.....
	 */
	/* bp = (uint *)&cpmp->cp_brgc1; */
	bp = (volatile uint *)(&pquicc->brgc[0].l);
	bp += brg;
	*bp = ((BRG_UART_CLK / rate - 1) << 1) | CPM_BRG_EN;
}