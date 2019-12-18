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
typedef  int u32 ;
struct e1000_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int E1000_CTRL_MDC ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH () ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void e1000_raise_mdi_clk(struct e1000_hw *hw, u32 *ctrl)
{
	/* Raise the clock input to the Management Data Clock (by setting the MDC
	 * bit), and then delay 10 microseconds.
	 */
	ew32(CTRL, (*ctrl | E1000_CTRL_MDC));
	E1000_WRITE_FLUSH();
	udelay(10);
}