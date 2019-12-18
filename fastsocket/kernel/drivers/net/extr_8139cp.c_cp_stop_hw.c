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
struct cp_private {scalar_t__ tx_tail; scalar_t__ tx_head; scalar_t__ rx_tail; } ;

/* Variables and functions */
 int /*<<< orphan*/  Cmd ; 
 int /*<<< orphan*/  CpCmd ; 
 int /*<<< orphan*/  IntrMask ; 
 int /*<<< orphan*/  IntrStatus ; 
 int /*<<< orphan*/  cpr16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpw16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpw16_f (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpw8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cp_stop_hw (struct cp_private *cp)
{
	cpw16(IntrStatus, ~(cpr16(IntrStatus)));
	cpw16_f(IntrMask, 0);
	cpw8(Cmd, 0);
	cpw16_f(CpCmd, 0);
	cpw16_f(IntrStatus, ~(cpr16(IntrStatus)));

	cp->rx_tail = 0;
	cp->tx_head = cp->tx_tail = 0;
}