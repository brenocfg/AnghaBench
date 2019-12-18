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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  esp_bt_eir_type_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BTM_CheckEirData (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

uint8_t *esp_bt_gap_resolve_eir_data(uint8_t *eir, esp_bt_eir_type_t type, uint8_t *length)
{
    if (!eir) {
        return NULL;
    }

    return BTM_CheckEirData(eir, type, length);
}