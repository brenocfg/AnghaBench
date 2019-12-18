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
typedef  int u_char ;
struct TYPE_3__ {int /*<<< orphan*/  cfg_reg; } ;
struct TYPE_4__ {TYPE_1__ diva; } ;
struct IsdnCardState {TYPE_2__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  memwritereg (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
MemWriteISAC_IPAC(struct IsdnCardState *cs, u_char offset, u_char value)
{
	memwritereg(cs->hw.diva.cfg_reg, offset|0x80, value);
}