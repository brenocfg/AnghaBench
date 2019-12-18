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
struct wl12xx_sdio_glue {int /*<<< orphan*/  core; } ;
struct sdio_func {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct wl12xx_sdio_glue*) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (int /*<<< orphan*/ *) ; 
 struct wl12xx_sdio_glue* sdio_get_drvdata (struct sdio_func*) ; 

__attribute__((used)) static void wl1271_remove(struct sdio_func *func)
{
	struct wl12xx_sdio_glue *glue = sdio_get_drvdata(func);

	/* Undo decrement done above in wl1271_probe */
	pm_runtime_get_noresume(&func->dev);

	platform_device_unregister(glue->core);
	kfree(glue);
}