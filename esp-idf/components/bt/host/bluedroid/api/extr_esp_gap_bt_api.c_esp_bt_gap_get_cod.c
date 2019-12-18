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
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  esp_bt_cod_t ;

/* Variables and functions */
 int /*<<< orphan*/  btc_gap_bt_get_cod (int /*<<< orphan*/ *) ; 

esp_err_t esp_bt_gap_get_cod(esp_bt_cod_t *cod)
{
    return btc_gap_bt_get_cod(cod);
}