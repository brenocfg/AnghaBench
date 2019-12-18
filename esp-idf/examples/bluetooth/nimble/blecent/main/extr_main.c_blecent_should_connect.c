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
struct ble_hs_adv_fields {int num_uuids16; TYPE_2__* uuids16; } ;
struct TYPE_3__ {int /*<<< orphan*/  val; } ;
struct ble_gap_disc_desc {scalar_t__ event_type; TYPE_1__ addr; int /*<<< orphan*/  length_data; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int /*<<< orphan*/  u; } ;

/* Variables and functions */
 scalar_t__ BLECENT_SVC_ALERT_UUID ; 
 scalar_t__ BLE_HCI_ADV_RPT_EVTYPE_ADV_IND ; 
 scalar_t__ BLE_HCI_ADV_RPT_EVTYPE_DIR_IND ; 
 char* CONFIG_EXAMPLE_PEER_ADDR ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,char*) ; 
 int ble_hs_adv_parse_fields (struct ble_hs_adv_fields*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ble_uuid_u16 (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * peer_addr ; 
 int /*<<< orphan*/  sscanf (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  tag ; 

__attribute__((used)) static int
blecent_should_connect(const struct ble_gap_disc_desc *disc)
{
    struct ble_hs_adv_fields fields;
    int rc;
    int i;

    /* The device has to be advertising connectability. */
    if (disc->event_type != BLE_HCI_ADV_RPT_EVTYPE_ADV_IND &&
            disc->event_type != BLE_HCI_ADV_RPT_EVTYPE_DIR_IND) {

        return 0;
    }

    rc = ble_hs_adv_parse_fields(&fields, disc->data, disc->length_data);
    if (rc != 0) {
        return rc;
    }

    if (strlen(CONFIG_EXAMPLE_PEER_ADDR) && (strncmp(CONFIG_EXAMPLE_PEER_ADDR, "ADDR_ANY", strlen("ADDR_ANY")) != 0)) {
        ESP_LOGI(tag, "Peer address from menuconfig: %s", CONFIG_EXAMPLE_PEER_ADDR);
        /* Convert string to address */
        sscanf(CONFIG_EXAMPLE_PEER_ADDR, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
               &peer_addr[5], &peer_addr[4], &peer_addr[3],
               &peer_addr[2], &peer_addr[1], &peer_addr[0]);
        if (memcmp(peer_addr, disc->addr.val, sizeof(disc->addr.val)) != 0) {
            return 0;
        }
    }

    /* The device has to advertise support for the Alert Notification
     * service (0x1811).
     */
    for (i = 0; i < fields.num_uuids16; i++) {
        if (ble_uuid_u16(&fields.uuids16[i].u) == BLECENT_SVC_ALERT_UUID) {
            return 1;
        }
    }

    return 0;
}