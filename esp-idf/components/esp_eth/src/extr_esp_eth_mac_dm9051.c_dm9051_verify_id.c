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
 int /*<<< orphan*/  DM9051_PIDH ; 
 int /*<<< orphan*/  DM9051_PIDL ; 
 int /*<<< orphan*/  DM9051_VIDH ; 
 int /*<<< orphan*/  DM9051_VIDL ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_VERSION ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  MAC_CHECK (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dm9051_register_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  err ; 

__attribute__((used)) static esp_err_t dm9051_verify_id(emac_dm9051_t *emac)
{
    esp_err_t ret = ESP_OK;
    uint8_t id[2];
    MAC_CHECK(dm9051_register_read(emac, DM9051_VIDL, &id[0]) == ESP_OK, "read VIDL failed", err, ESP_FAIL);
    MAC_CHECK(dm9051_register_read(emac, DM9051_VIDH, &id[1]) == ESP_OK, "read VIDH failed", err, ESP_FAIL);
    MAC_CHECK(0x0A == id[1] && 0x46 == id[0], "wrong Vendor ID", err, ESP_ERR_INVALID_VERSION);
    MAC_CHECK(dm9051_register_read(emac, DM9051_PIDL, &id[0]) == ESP_OK, "read PIDL failed", err, ESP_FAIL);
    MAC_CHECK(dm9051_register_read(emac, DM9051_PIDH, &id[1]) == ESP_OK, "read PIDH failed", err, ESP_FAIL);
    MAC_CHECK(0x90 == id[1] && 0x51 == id[0], "wrong Product ID", err, ESP_ERR_INVALID_VERSION);
    return ESP_OK;
err:
    return ret;
}