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
struct nand_chip {struct atmel_nand_host* priv; } ;
struct mtd_info {struct nand_chip* priv; } ;
struct atmel_nand_host {TYPE_1__* board; } ;
struct TYPE_2__ {int /*<<< orphan*/  rdy_pin_active_low; int /*<<< orphan*/  rdy_pin; } ;

/* Variables and functions */
 int gpio_get_value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_nand_device_ready(struct mtd_info *mtd)
{
	struct nand_chip *nand_chip = mtd->priv;
	struct atmel_nand_host *host = nand_chip->priv;

	return gpio_get_value(host->board->rdy_pin) ^
                !!host->board->rdy_pin_active_low;
}