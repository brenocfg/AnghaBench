#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  slot; int /*<<< orphan*/  (* io_int_enable ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__ host; } ;
typedef  TYPE_2__ sdmmc_card_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

esp_err_t sdmmc_io_enable_int(sdmmc_card_t* card)
{
    if (card->host.io_int_enable == NULL) {
        return ESP_ERR_NOT_SUPPORTED;
    }
    return (*card->host.io_int_enable)(card->host.slot);
}