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
struct wl12xx_sdio_glue {int /*<<< orphan*/  dev; } ;
struct sdio_func {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 struct wl12xx_sdio_glue* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct sdio_func* dev_to_sdio_func (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdio_claim_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_release_host (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_set_block_size (struct sdio_func*,unsigned int) ; 

__attribute__((used)) static void wl1271_sdio_set_block_size(struct device *child,
				       unsigned int blksz)
{
	struct wl12xx_sdio_glue *glue = dev_get_drvdata(child->parent);
	struct sdio_func *func = dev_to_sdio_func(glue->dev);

	sdio_claim_host(func);
	sdio_set_block_size(func, blksz);
	sdio_release_host(func);
}