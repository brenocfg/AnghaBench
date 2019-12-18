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
struct platform_device {int dummy; } ;
struct clk {int dummy; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  DUM_CTRL ; 
 int /*<<< orphan*/  IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  V_BAC_DISABLE_IDLE ; 
 struct clk* clk_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 int /*<<< orphan*/  clk_set_rate (struct clk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcd_reset () ; 

__attribute__((used)) static int sdum_suspend(struct platform_device *pdev, pm_message_t state)
{
	int retval = 0;
	struct clk *clk;

	clk = clk_get(0, "dum_ck");
	if (!IS_ERR(clk)) {
		clk_set_rate(clk, 0);
		clk_put(clk);
	} else
		retval = PTR_ERR(clk);

	/* disable BAC */
	DUM_CTRL = V_BAC_DISABLE_IDLE;

	/* LCD standby & turn off display */
	lcd_reset();

	return retval;
}