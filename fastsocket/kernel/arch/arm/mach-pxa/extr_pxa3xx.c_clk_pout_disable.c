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
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSCC ; 
 int /*<<< orphan*/  OSCC_PEN ; 

__attribute__((used)) static void clk_pout_disable(struct clk *clk)
{
	OSCC &= ~OSCC_PEN;
}