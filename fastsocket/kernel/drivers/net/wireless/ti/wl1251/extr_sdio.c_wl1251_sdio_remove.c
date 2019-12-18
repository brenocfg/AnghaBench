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
struct wl1251_sdio {int dummy; } ;
struct wl1251 {scalar_t__ irq; struct wl1251_sdio* if_priv; } ;
struct sdio_func {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct wl1251*) ; 
 int /*<<< orphan*/  kfree (struct wl1251_sdio*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_disable_func (struct sdio_func*) ; 
 struct wl1251* sdio_get_drvdata (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_irq (struct sdio_func*) ; 
 int /*<<< orphan*/  wl1251_free_hw (struct wl1251*) ; 

__attribute__((used)) static void wl1251_sdio_remove(struct sdio_func *func)
{
	struct wl1251 *wl = sdio_get_drvdata(func);
	struct wl1251_sdio *wl_sdio = wl->if_priv;

	/* Undo decrement done above in wl1251_probe */
	pm_runtime_get_noresume(&func->dev);

	if (wl->irq)
		free_irq(wl->irq, wl);
	wl1251_free_hw(wl);
	kfree(wl_sdio);

	sdio_claim_host(func);
	sdio_release_irq(func);
	sdio_disable_func(func);
	sdio_release_host(func);
}