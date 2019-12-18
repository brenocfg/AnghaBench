#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_3__ {int /*<<< orphan*/  slc0_intvec; } ;
struct TYPE_4__ {TYPE_1__ intvec_tohost; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  SDIO_SLAVE_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__ SLC ; 

esp_err_t sdio_slave_send_host_int(uint8_t pos)
{
    SDIO_SLAVE_CHECK(pos < 8, "interrupt num invalid", ESP_ERR_INVALID_ARG);
    SLC.intvec_tohost.slc0_intvec = BIT(pos);
    return ESP_OK;
}