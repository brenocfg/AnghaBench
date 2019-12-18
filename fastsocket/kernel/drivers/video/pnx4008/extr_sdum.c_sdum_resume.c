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

/* Variables and functions */
 int BAC_ENABLED ; 
 int DUM_CTRL ; 
 int /*<<< orphan*/  IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int V_BAC_DISABLE_TRIG ; 
 int V_BAC_ENABLE ; 
 int V_MUX_RESET ; 
 struct clk* clk_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  clk_put (struct clk*) ; 
 int /*<<< orphan*/  clk_set_rate (struct clk*,int) ; 
 int /*<<< orphan*/  lcd_init () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int sdum_resume(struct platform_device *pdev)
{
	int retval = 0;
	struct clk *clk;

	clk = clk_get(0, "dum_ck");
	if (!IS_ERR(clk)) {
		clk_set_rate(clk, 1);
		clk_put(clk);
	} else
		retval = PTR_ERR(clk);

	/* wait for BAC disable */
	DUM_CTRL = V_BAC_DISABLE_TRIG;

	while (DUM_CTRL & BAC_ENABLED)
		udelay(10);

	/* re-init LCD */
	lcd_init();

	/* enable BAC and reset MUX */
	DUM_CTRL = V_BAC_ENABLE;
	udelay(1);
	DUM_CTRL = V_MUX_RESET;
	return 0;
}