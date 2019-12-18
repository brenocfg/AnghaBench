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
typedef  int /*<<< orphan*/  esp_eth_phy_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_FAIL ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  PHY_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err ; 
 scalar_t__ ip101_pwrctl (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static esp_err_t ip101_deinit(esp_eth_phy_t *phy)
{
    /* Power off Ethernet PHY */
    PHY_CHECK(ip101_pwrctl(phy, false) == ESP_OK, "power control failed", err);
    return ESP_OK;
err:
    return ESP_FAIL;
}