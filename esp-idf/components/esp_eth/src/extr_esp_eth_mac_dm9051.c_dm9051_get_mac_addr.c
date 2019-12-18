#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ esp_err_t ;
struct TYPE_4__ {int /*<<< orphan*/ * addr; } ;
typedef  TYPE_1__ emac_dm9051_t ;

/* Variables and functions */
 scalar_t__ DM9051_PAR ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  MAC_CHECK (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dm9051_register_read (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err ; 

__attribute__((used)) static esp_err_t dm9051_get_mac_addr(emac_dm9051_t *emac)
{
    esp_err_t ret = ESP_OK;
    for (int i = 0; i < 6; i++) {
        MAC_CHECK(dm9051_register_read(emac, DM9051_PAR + i, &emac->addr[i]) == ESP_OK, "read PAR failed", err, ESP_FAIL);
    }
    return ESP_OK;
err:
    return ret;
}