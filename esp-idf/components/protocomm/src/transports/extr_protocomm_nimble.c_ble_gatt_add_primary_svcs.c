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
struct ble_gatt_svc_def {struct ble_gatt_chr_def* characteristics; int /*<<< orphan*/  type; } ;
struct ble_gatt_chr_def {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLE_GATT_SVC_TYPE_PRIMARY ; 
 int ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ calloc (int,int) ; 
 int num_chr_dsc ; 

__attribute__((used)) static int
ble_gatt_add_primary_svcs(struct ble_gatt_svc_def *gatt_db_svcs, int char_count)
{
    /* Remember the count of characteristics here, as it will be used to free
     * memory afterwards */
    num_chr_dsc = char_count;
    gatt_db_svcs->type = BLE_GATT_SVC_TYPE_PRIMARY;

    /* Allocate (number of characteristics + 1) memory for characteristics, the
     * addtional characteristic consist of all 0s indicating end of
     * characteristics */
    gatt_db_svcs->characteristics = (struct ble_gatt_chr_def *) calloc((char_count + 1),
                                    sizeof(struct ble_gatt_chr_def));
    if (gatt_db_svcs->characteristics == NULL) {
        ESP_LOGE(TAG, "Memory allocation for GATT characteristics failed");
        return ESP_ERR_NO_MEM;
    }
    return 0;
}