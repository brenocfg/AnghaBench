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
struct ds1wm_data {int /*<<< orphan*/  map; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ds1wm_down (struct ds1wm_data*) ; 
 int /*<<< orphan*/  ds1wm_master ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ds1wm_data*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ds1wm_data*) ; 
 struct ds1wm_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  w1_remove_master_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ds1wm_remove(struct platform_device *pdev)
{
	struct ds1wm_data *ds1wm_data = platform_get_drvdata(pdev);

	w1_remove_master_device(&ds1wm_master);
	ds1wm_down(ds1wm_data);
	free_irq(ds1wm_data->irq, ds1wm_data);
	iounmap(ds1wm_data->map);
	kfree(ds1wm_data);

	return 0;
}