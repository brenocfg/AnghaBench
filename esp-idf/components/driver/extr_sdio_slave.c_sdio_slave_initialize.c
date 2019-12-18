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
typedef  int /*<<< orphan*/  sdio_slave_config_t ;
typedef  int /*<<< orphan*/ * intr_handle_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_2__ {int /*<<< orphan*/ * intr_handle; } ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  ETS_SLC0_INTR_SOURCE ; 
 TYPE_1__ context ; 
 scalar_t__ esp_intr_alloc (int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ init_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdio_intr ; 
 scalar_t__ sdio_slave_hw_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdio_slave_reset () ; 

esp_err_t sdio_slave_initialize(sdio_slave_config_t *config)
{
    esp_err_t r;
    intr_handle_t intr_handle = NULL;
    const int flags = 0;
    r = esp_intr_alloc(ETS_SLC0_INTR_SOURCE, flags, sdio_intr, NULL, &intr_handle);
    if (r != ESP_OK) return r;

    r = sdio_slave_hw_init(config);
    if (r != ESP_OK) return r;
    r = init_context(config);
    if (r != ESP_OK) return r;
    context.intr_handle = intr_handle;

    sdio_slave_reset();
    return ESP_OK;
}