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
typedef  int /*<<< orphan*/  u_short ;
struct s_smc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PB ; 
 int /*<<< orphan*/  PLC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PL_INTR_EVENT ; 
 int /*<<< orphan*/  inpw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plc_irq (struct s_smc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void plc1_irq(struct s_smc *smc)
{
	u_short	st = inpw(PLC(PB,PL_INTR_EVENT)) ;

	plc_irq(smc,PB,st) ;
}