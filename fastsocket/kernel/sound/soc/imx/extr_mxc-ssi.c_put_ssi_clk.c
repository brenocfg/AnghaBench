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

/* Variables and functions */
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ssi_clk0 ; 
 int /*<<< orphan*/ * ssi_clk1 ; 

void put_ssi_clk(int ssi)
{
	switch (ssi) {
	case 0:
		clk_put(ssi_clk0);
		ssi_clk0 = NULL;
		break;
	case 1:
		clk_put(ssi_clk1);
		ssi_clk1 = NULL;
		break;
	}
}