#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  uu; int /*<<< orphan*/  len; } ;
typedef  TYPE_2__ tSDP_UUID ;
struct TYPE_10__ {int /*<<< orphan*/  len; int /*<<< orphan*/  uuid; } ;
typedef  TYPE_3__ esp_bt_uuid_t ;
struct TYPE_12__ {int /*<<< orphan*/  address; } ;
struct TYPE_8__ {TYPE_5__ bda; TYPE_3__ uuid; } ;
struct TYPE_11__ {TYPE_1__ get_rmt_srv_rcd; } ;
typedef  TYPE_4__ btc_gap_bt_args_t ;
typedef  TYPE_5__ bt_bdaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DmDiscoverUUID (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bte_dm_remote_service_record_evt ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btc_gap_bt_get_remote_service_record(btc_gap_bt_args_t *arg)
{
    esp_bt_uuid_t *uuid = &arg->get_rmt_srv_rcd.uuid;
    bt_bdaddr_t *remote_bda = &arg->get_rmt_srv_rcd.bda;

    tSDP_UUID sdp_uuid;

    sdp_uuid.len = uuid->len;
    memcpy(&sdp_uuid.uu, &uuid->uuid, uuid->len);

    BTA_DmDiscoverUUID(remote_bda->address, &sdp_uuid,
                       bte_dm_remote_service_record_evt, TRUE);
}