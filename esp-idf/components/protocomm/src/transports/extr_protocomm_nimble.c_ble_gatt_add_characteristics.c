#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ble_gatt_chr_def {int flags; int /*<<< orphan*/ * uuid; int /*<<< orphan*/  access_cb; } ;
typedef  int /*<<< orphan*/  ble_uuid_t ;
struct TYPE_7__ {int /*<<< orphan*/  type; } ;
struct TYPE_9__ {void* value; TYPE_1__ u; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ ble_uuid128_t ;
struct TYPE_10__ {TYPE_2__* g_nu_lookup; } ;
struct TYPE_8__ {TYPE_3__ uuid; } ;

/* Variables and functions */
 int BLE_GATT_CHR_F_READ ; 
 int BLE_GATT_CHR_F_WRITE ; 
 int BLE_UUID128_VAL_LENGTH ; 
 int /*<<< orphan*/  BLE_UUID_TYPE_128 ; 
 int ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 
 TYPE_3__* ble_uuid_base ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  gatt_svr_chr_access ; 
 int /*<<< orphan*/  memcpy (void*,TYPE_3__*,int) ; 
 TYPE_4__* protoble_internal ; 

__attribute__((used)) static int
ble_gatt_add_characteristics(struct ble_gatt_chr_def *characteristics, int idx)
{
    /* Prepare 128 bit UUID of characteristics using custom base 128
     * bit UUID and replacing byte 12 and 13 with corresponding protocom
     * endpoint 16 bit UUID value. */
    ble_uuid128_t temp_uuid128_name = {0};
    temp_uuid128_name.u.type = BLE_UUID_TYPE_128;
    memcpy(temp_uuid128_name.value, ble_uuid_base, BLE_UUID128_VAL_LENGTH);
    memcpy(&temp_uuid128_name.value[12], &protoble_internal->g_nu_lookup[idx].uuid, 2);

    (characteristics + idx)->flags = BLE_GATT_CHR_F_READ | BLE_GATT_CHR_F_WRITE;
    (characteristics + idx)->access_cb = gatt_svr_chr_access;

    /* Out of 128 bit UUID, 16 bits from g_nu_lookup table. Currently
     * g_nu_lookup table has 16 bit UUID, XXX this can be changed to 128 bit UUID
     * in future. For time being continue using 16 bit UUID on top of base 128
     * bit service UUID */
    (characteristics + idx)->uuid = (ble_uuid_t *)calloc(1,
                                    sizeof(ble_uuid128_t));
    if ((characteristics + idx)->uuid == NULL) {
        ESP_LOGE(TAG, "Error allocating memory for characteristic UUID");
        return ESP_ERR_NO_MEM;
    }
    memcpy((void *)(characteristics + idx)->uuid, &temp_uuid128_name,
           sizeof(ble_uuid128_t));

    return 0;
}