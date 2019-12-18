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
struct sh_mobile_lcdc_priv {int lddckr; int /*<<< orphan*/  dev; int /*<<< orphan*/  hw_usecnt; int /*<<< orphan*/  dot_clk; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
#define  LCDC_CLK_BUS 130 
#define  LCDC_CLK_EXTERNAL 129 
#define  LCDC_CLK_PERIPHERAL 128 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_resume (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_mobile_lcdc_setup_clocks(struct platform_device *pdev,
				       int clock_source,
				       struct sh_mobile_lcdc_priv *priv)
{
	char *str;
	int icksel;

	switch (clock_source) {
	case LCDC_CLK_BUS: str = "bus_clk"; icksel = 0; break;
	case LCDC_CLK_PERIPHERAL: str = "peripheral_clk"; icksel = 1; break;
	case LCDC_CLK_EXTERNAL: str = NULL; icksel = 2; break;
	default:
		return -EINVAL;
	}

	priv->lddckr = icksel << 16;

	if (str) {
		priv->dot_clk = clk_get(&pdev->dev, str);
		if (IS_ERR(priv->dot_clk)) {
			dev_err(&pdev->dev, "cannot get dot clock %s\n", str);
			return PTR_ERR(priv->dot_clk);
		}
	}
	atomic_set(&priv->hw_usecnt, -1);

	/* Runtime PM support involves two step for this driver:
	 * 1) Enable Runtime PM
	 * 2) Force Runtime PM Resume since hardware is accessed from probe()
	 */
	pm_runtime_enable(priv->dev);
	pm_runtime_resume(priv->dev);
	return 0;
}