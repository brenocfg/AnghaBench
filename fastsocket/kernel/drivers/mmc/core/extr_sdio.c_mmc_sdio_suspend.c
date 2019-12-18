#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* driver; } ;
struct sdio_func {TYPE_3__ dev; } ;
struct mmc_host {TYPE_1__* card; } ;
struct dev_pm_ops {int (* suspend ) (TYPE_3__*) ;int /*<<< orphan*/  (* resume ) (TYPE_3__*) ;} ;
struct TYPE_6__ {struct dev_pm_ops* pm; } ;
struct TYPE_5__ {int sdio_funcs; struct sdio_func** sdio_func; } ;

/* Variables and functions */
 int ENOSYS ; 
 scalar_t__ sdio_func_present (struct sdio_func*) ; 
 int stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 

__attribute__((used)) static int mmc_sdio_suspend(struct mmc_host *host)
{
	int i, err = 0;

	for (i = 0; i < host->card->sdio_funcs; i++) {
		struct sdio_func *func = host->card->sdio_func[i];
		if (func && sdio_func_present(func) && func->dev.driver) {
			const struct dev_pm_ops *pmops = func->dev.driver->pm;
			if (!pmops || !pmops->suspend || !pmops->resume) {
				/* force removal of entire card in that case */
				err = -ENOSYS;
			} else
				err = pmops->suspend(&func->dev);
			if (err)
				break;
		}
	}
	while (err && --i >= 0) {
		struct sdio_func *func = host->card->sdio_func[i];
		if (func && sdio_func_present(func) && func->dev.driver) {
			const struct dev_pm_ops *pmops = func->dev.driver->pm;
			pmops->resume(&func->dev);
		}
	}

	return err;
}