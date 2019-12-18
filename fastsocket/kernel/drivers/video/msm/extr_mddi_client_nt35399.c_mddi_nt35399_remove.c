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
struct panel_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct panel_info*) ; 
 struct panel_info* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  setup_vsync (struct panel_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mddi_nt35399_remove(struct platform_device *pdev)
{
	struct panel_info *panel = platform_get_drvdata(pdev);

	setup_vsync(panel, 0);
	kfree(panel);
	return 0;
}