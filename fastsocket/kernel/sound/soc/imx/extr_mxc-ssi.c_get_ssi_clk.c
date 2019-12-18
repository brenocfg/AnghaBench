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
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  ssi_clk0 ; 
 int /*<<< orphan*/  ssi_clk1 ; 

int get_ssi_clk(int ssi, struct device *dev)
{
	switch (ssi) {
	case 0:
		ssi_clk0 = clk_get(dev, "ssi1");
		if (IS_ERR(ssi_clk0))
			return PTR_ERR(ssi_clk0);
		return 0;
	case 1:
		ssi_clk1 = clk_get(dev, "ssi2");
		if (IS_ERR(ssi_clk1))
			return PTR_ERR(ssi_clk1);
		return 0;
	default:
		return -EINVAL;
	}
}