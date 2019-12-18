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
struct clk {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 unsigned long CRM_1DIVIDER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MXC_CRMAP_ACDER2 ; 
 int /*<<< orphan*/  NFCDIV ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long clk_nfc_get_rate(struct clk *clk)
{
	return clk_get_rate(clk->parent) /
		CRM_1DIVIDER(MXC_CRMAP_ACDER2, NFCDIV);
}