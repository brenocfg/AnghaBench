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
struct platform_device {int id; int /*<<< orphan*/  dev; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  IS_ERR (struct clk*) ; 
 struct clk* clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 int /*<<< orphan*/  clk_set_rate (struct clk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int set_clock_stop(struct platform_device *pdev)
{
	struct clk *clk;
	char name[10];
	int retval = 0;

	snprintf(name, 10, "i2c%d_ck", pdev->id);
	clk = clk_get(&pdev->dev, name);
	if (!IS_ERR(clk)) {
		clk_set_rate(clk, 0);
		clk_put(clk);
	} else
		retval = -ENOENT;

	return retval;
}