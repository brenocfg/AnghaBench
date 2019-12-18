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
struct icst307_vco {int dummy; } ;
struct clk {int /*<<< orphan*/  params; } ;

/* Variables and functions */
 int icst307_khz (int /*<<< orphan*/ ,struct icst307_vco) ; 
 struct icst307_vco icst307_khz_to_vco (int /*<<< orphan*/ ,unsigned long) ; 

long clk_round_rate(struct clk *clk, unsigned long rate)
{
	struct icst307_vco vco;
	vco = icst307_khz_to_vco(clk->params, rate / 1000);
	return icst307_khz(clk->params, vco) * 1000;
}