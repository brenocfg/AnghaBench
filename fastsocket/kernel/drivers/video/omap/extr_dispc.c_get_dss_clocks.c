#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* dss_54m_fck; void* dss1_fck; void* dss_ick; TYPE_1__* fbdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 void* clk_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  clk_put (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__ dispc ; 

__attribute__((used)) static int get_dss_clocks(void)
{
	dispc.dss_ick = clk_get(dispc.fbdev->dev, "ick");
	if (IS_ERR(dispc.dss_ick)) {
		dev_err(dispc.fbdev->dev, "can't get ick\n");
		return PTR_ERR(dispc.dss_ick);
	}

	dispc.dss1_fck = clk_get(dispc.fbdev->dev, "dss1_fck");
	if (IS_ERR(dispc.dss1_fck)) {
		dev_err(dispc.fbdev->dev, "can't get dss1_fck\n");
		clk_put(dispc.dss_ick);
		return PTR_ERR(dispc.dss1_fck);
	}

	dispc.dss_54m_fck = clk_get(dispc.fbdev->dev, "tv_fck");
	if (IS_ERR(dispc.dss_54m_fck)) {
		dev_err(dispc.fbdev->dev, "can't get tv_fck\n");
		clk_put(dispc.dss_ick);
		clk_put(dispc.dss1_fck);
		return PTR_ERR(dispc.dss_54m_fck);
	}

	return 0;
}