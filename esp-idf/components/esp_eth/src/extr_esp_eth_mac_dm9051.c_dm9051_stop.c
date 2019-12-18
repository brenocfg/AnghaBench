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
typedef  int uint8_t ;
typedef  scalar_t__ esp_err_t ;
typedef  int /*<<< orphan*/  emac_dm9051_t ;

/* Variables and functions */
 int /*<<< orphan*/  DM9051_IMR ; 
 int /*<<< orphan*/  DM9051_RCR ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  MAC_CHECK (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RCR_RXEN ; 
 scalar_t__ dm9051_register_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ dm9051_register_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  err ; 

__attribute__((used)) static esp_err_t dm9051_stop(emac_dm9051_t *emac)
{
    esp_err_t ret = ESP_OK;
    /* disable interrupt */
    MAC_CHECK(dm9051_register_write(emac, DM9051_IMR, 0x00) == ESP_OK, "write IMR failed", err, ESP_FAIL);
    /* disable rx */
    uint8_t rcr = 0;
    MAC_CHECK(dm9051_register_read(emac, DM9051_RCR, &rcr) == ESP_OK, "read RCR failed", err, ESP_FAIL);
    rcr &= ~RCR_RXEN;
    MAC_CHECK(dm9051_register_write(emac, DM9051_RCR, rcr) == ESP_OK, "write RCR failed", err, ESP_FAIL);
    return ESP_OK;
err:
    return ret;
}