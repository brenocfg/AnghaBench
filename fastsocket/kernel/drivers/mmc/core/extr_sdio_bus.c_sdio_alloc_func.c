#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * bus; int /*<<< orphan*/ * parent; } ;
struct sdio_func {TYPE_1__ dev; struct mmc_card* card; } ;
struct mmc_card {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct sdio_func* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 struct sdio_func* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_bus_type ; 
 int /*<<< orphan*/  sdio_release_func ; 

struct sdio_func *sdio_alloc_func(struct mmc_card *card)
{
	struct sdio_func *func;

	func = kzalloc(sizeof(struct sdio_func), GFP_KERNEL);
	if (!func)
		return ERR_PTR(-ENOMEM);

	func->card = card;

	device_initialize(&func->dev);

	func->dev.parent = &card->dev;
	func->dev.bus = &sdio_bus_type;
	func->dev.release = sdio_release_func;

	return func;
}