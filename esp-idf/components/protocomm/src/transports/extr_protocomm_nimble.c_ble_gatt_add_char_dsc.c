#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct ble_gatt_dsc_def {void* arg; int /*<<< orphan*/  access_cb; int /*<<< orphan*/  att_flags; int /*<<< orphan*/ * uuid; } ;
struct ble_gatt_chr_def {struct ble_gatt_dsc_def* descriptors; } ;
typedef  int /*<<< orphan*/  ble_uuid_t ;
typedef  int /*<<< orphan*/  ble_uuid16_t ;
struct TYPE_4__ {TYPE_1__* g_nu_lookup; } ;
struct TYPE_3__ {scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_ATT_F_READ ; 
 int /*<<< orphan*/ * BLE_UUID16_DECLARE (int /*<<< orphan*/ ) ; 
 int ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  gatt_svr_dsc_access ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* protoble_internal ; 

__attribute__((used)) static int
ble_gatt_add_char_dsc(struct ble_gatt_chr_def *characteristics, int idx, uint16_t dsc_uuid)
{
    ble_uuid_t *uuid16 = BLE_UUID16_DECLARE(dsc_uuid);

    /* Allocate memory for 2 descriptors, the 2nd descriptor shall be all NULLs
     * to indicate End of Descriptors. */
    (characteristics + idx)->descriptors = (struct ble_gatt_dsc_def *) calloc(2,
                                           sizeof(struct ble_gatt_dsc_def));
    if ((characteristics + idx)->descriptors == NULL) {
        ESP_LOGE(TAG, "Error while allocating memory for characteristic descriptor");
        return ESP_ERR_NO_MEM;
    }

    (characteristics + idx)->descriptors[0].uuid = (ble_uuid_t *) calloc(1,
            sizeof(ble_uuid16_t));
    if ((characteristics + idx)->descriptors[0].uuid == NULL) {
        ESP_LOGE(TAG, "Error while allocating memory for characteristic descriptor");
        return ESP_ERR_NO_MEM;
    }
    memcpy((void *)(characteristics + idx)->descriptors[0].uuid, uuid16,
           sizeof(ble_uuid16_t));
    (characteristics + idx)->descriptors[0].att_flags = BLE_ATT_F_READ;
    (characteristics + idx)->descriptors[0].access_cb = gatt_svr_dsc_access;
    (characteristics + idx)->descriptors[0].arg = (void *)
            protoble_internal->g_nu_lookup[idx].name;

    return 0;
}