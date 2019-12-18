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
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  TickType_t ;
struct TYPE_2__ {int /*<<< orphan*/ * events; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  SDIO_SLAVE_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ context ; 
 int /*<<< orphan*/  xSemaphoreTake (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

esp_err_t sdio_slave_wait_int(int pos, TickType_t wait)
{
    SDIO_SLAVE_CHECK(pos >= 0 && pos < 8, "interrupt num invalid", ESP_ERR_INVALID_ARG);
    return xSemaphoreTake(context.events[pos], wait);
}