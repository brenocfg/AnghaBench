#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBT_TRANSPORT ;
typedef  int tBTM_STATUS ;
typedef  int /*<<< orphan*/  tBTA_STATUS ;
typedef  int /*<<< orphan*/  (* tBTA_DM_ENCRYPT_CBACK ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
typedef  size_t UINT8 ;
struct TYPE_5__ {size_t count; TYPE_1__* peer_device; } ;
struct TYPE_6__ {TYPE_2__ device_list; } ;
struct TYPE_4__ {scalar_t__ conn_state; int /*<<< orphan*/  (* p_encrypt_cback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  peer_bdaddr; } ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  BTA_BUSY ; 
 scalar_t__ BTA_DM_CONNECTED ; 
 int /*<<< orphan*/  BTA_FAILURE ; 
 int /*<<< orphan*/  BTA_NO_RESOURCES ; 
 int /*<<< orphan*/  BTA_SUCCESS ; 
 int /*<<< orphan*/  BTA_WRONG_MODE ; 
#define  BTM_BUSY 131 
#define  BTM_NO_RESOURCES 130 
#define  BTM_SUCCESS 129 
#define  BTM_WRONG_MODE 128 
 int /*<<< orphan*/  UNUSED (void*) ; 
 scalar_t__ bdcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ bta_dm_cb ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bta_dm_encrypt_cback(BD_ADDR bd_addr, tBT_TRANSPORT transport, void *p_ref_data, tBTM_STATUS result)
{
    tBTA_STATUS   bta_status = BTA_SUCCESS;
    tBTA_DM_ENCRYPT_CBACK *p_callback = NULL;
    UINT8   i ;
    UNUSED(p_ref_data);

    for (i = 0; i < bta_dm_cb.device_list.count; i++) {
        if (bdcmp( bta_dm_cb.device_list.peer_device[i].peer_bdaddr, bd_addr) == 0 &&
                bta_dm_cb.device_list.peer_device[i].conn_state == BTA_DM_CONNECTED) {
            break;
        }
    }

    if (i < bta_dm_cb.device_list.count) {
        p_callback = bta_dm_cb.device_list.peer_device[i].p_encrypt_cback;
        bta_dm_cb.device_list.peer_device[i].p_encrypt_cback = NULL;
    }

    switch (result) {
    case BTM_SUCCESS:
        break;
    case BTM_WRONG_MODE:
        bta_status = BTA_WRONG_MODE;
        break;
    case BTM_NO_RESOURCES:
        bta_status = BTA_NO_RESOURCES;
        break;
    case BTM_BUSY:
        bta_status = BTA_BUSY;
        break;
    default:
        bta_status = BTA_FAILURE;
        break;
    }

    APPL_TRACE_DEBUG("bta_dm_encrypt_cback status =%d p_callback=%p", bta_status, p_callback);

    if (p_callback) {
        (*p_callback)(bd_addr, transport, bta_status);
    }
}