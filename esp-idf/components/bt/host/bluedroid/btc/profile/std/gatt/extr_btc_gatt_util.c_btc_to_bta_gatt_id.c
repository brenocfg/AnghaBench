#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  uuid; int /*<<< orphan*/  inst_id; } ;
typedef  TYPE_1__ tBTA_GATT_ID ;
struct TYPE_6__ {int /*<<< orphan*/  uuid; int /*<<< orphan*/  inst_id; } ;
typedef  TYPE_2__ esp_gatt_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  btc_to_bta_uuid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void btc_to_bta_gatt_id(tBTA_GATT_ID *p_dest, esp_gatt_id_t *p_src)
{
    p_dest->inst_id = p_src->inst_id;
    btc_to_bta_uuid(&p_dest->uuid, &p_src->uuid);
}