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
struct TYPE_7__ {int /*<<< orphan*/  layer_specific; } ;
struct TYPE_8__ {TYPE_1__ hdr; int /*<<< orphan*/  handle; } ;
struct TYPE_9__ {TYPE_2__ api_confirm; } ;
typedef  TYPE_3__ tBTA_GATTC_DATA ;
struct TYPE_10__ {scalar_t__ transport; int /*<<< orphan*/  bda; } ;
typedef  TYPE_4__ tBTA_GATTC_CLCB ;
typedef  int /*<<< orphan*/  UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_ERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTA_ALL_APP_ID ; 
 int /*<<< orphan*/  BTA_ID_GATTC ; 
 scalar_t__ BTA_TRANSPORT_BR_EDR ; 
 scalar_t__ GATTC_SendHandleValueConfirm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GATT_SUCCESS ; 
 int /*<<< orphan*/  bta_sys_busy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_sys_idle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bta_gattc_confirm(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    UINT16 handle = p_data->api_confirm.handle;

    if (GATTC_SendHandleValueConfirm(p_data->api_confirm.hdr.layer_specific, handle)
        != GATT_SUCCESS) {
            APPL_TRACE_ERROR("bta_gattc_confirm to handle [0x%04x] failed", handle);
    } else {
        /* if over BR_EDR, inform PM for mode change */
        if (p_clcb->transport == BTA_TRANSPORT_BR_EDR) {
            bta_sys_busy(BTA_ID_GATTC, BTA_ALL_APP_ID, p_clcb->bda);
            bta_sys_idle(BTA_ID_GATTC, BTA_ALL_APP_ID, p_clcb->bda);
        }
    }
}