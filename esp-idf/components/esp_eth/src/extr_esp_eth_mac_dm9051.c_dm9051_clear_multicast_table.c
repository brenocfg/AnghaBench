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
typedef  scalar_t__ esp_err_t ;
typedef  int /*<<< orphan*/  emac_dm9051_t ;

/* Variables and functions */
 scalar_t__ DM9051_BCASTCR ; 
 scalar_t__ DM9051_MAR ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  MAC_CHECK (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dm9051_register_write (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  err ; 

__attribute__((used)) static esp_err_t dm9051_clear_multicast_table(emac_dm9051_t *emac)
{
    esp_err_t ret = ESP_OK;
    /* rx broadcast packet control by bit7 of MAC register 1DH */
    MAC_CHECK(dm9051_register_write(emac, DM9051_BCASTCR, 0x00) == ESP_OK, "write BCASTCR failed", err, ESP_FAIL);
    for (int i = 0; i < 7; i++) {
        MAC_CHECK(dm9051_register_write(emac, DM9051_MAR + i, 0x00) == ESP_OK, "write MAR failed", err, ESP_FAIL);
    }
    /* enable receive broadcast paclets */
    MAC_CHECK(dm9051_register_write(emac, DM9051_MAR + 7, 0x80) == ESP_OK, "write MAR failed", err, ESP_FAIL);
    return ESP_OK;
err:
    return ret;
}