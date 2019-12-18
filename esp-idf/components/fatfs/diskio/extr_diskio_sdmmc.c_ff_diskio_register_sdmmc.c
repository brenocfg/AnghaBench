#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sdmmc_card_t ;
struct TYPE_3__ {int /*<<< orphan*/ * ioctl; int /*<<< orphan*/ * write; int /*<<< orphan*/ * read; int /*<<< orphan*/ * status; int /*<<< orphan*/ * init; } ;
typedef  TYPE_1__ ff_diskio_impl_t ;
typedef  size_t BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ff_diskio_register (size_t,TYPE_1__ const*) ; 
 int /*<<< orphan*/  ff_sdmmc_initialize ; 
 int /*<<< orphan*/  ff_sdmmc_ioctl ; 
 int /*<<< orphan*/  ff_sdmmc_read ; 
 int /*<<< orphan*/  ff_sdmmc_status ; 
 int /*<<< orphan*/  ff_sdmmc_write ; 
 int /*<<< orphan*/ ** s_cards ; 

void ff_diskio_register_sdmmc(BYTE pdrv, sdmmc_card_t* card)
{
    static const ff_diskio_impl_t sdmmc_impl = {
        .init = &ff_sdmmc_initialize,
        .status = &ff_sdmmc_status,
        .read = &ff_sdmmc_read,
        .write = &ff_sdmmc_write,
        .ioctl = &ff_sdmmc_ioctl
    };
    s_cards[pdrv] = card;
    ff_diskio_register(pdrv, &sdmmc_impl);
}