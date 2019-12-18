#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  handle; TYPE_3__* dsc_def; } ;
struct TYPE_8__ {int /*<<< orphan*/  val_handle; int /*<<< orphan*/  def_handle; TYPE_1__* chr_def; } ;
struct TYPE_12__ {int /*<<< orphan*/  handle; TYPE_5__* svc_def; } ;
struct ble_gatt_register_ctxt {int op; TYPE_4__ dsc; TYPE_2__ chr; TYPE_6__ svc; } ;
struct TYPE_11__ {int /*<<< orphan*/  uuid; } ;
struct TYPE_9__ {int /*<<< orphan*/  uuid; } ;
struct TYPE_7__ {int /*<<< orphan*/  uuid; } ;

/* Variables and functions */
#define  BLE_GATT_REGISTER_OP_CHR 130 
#define  BLE_GATT_REGISTER_OP_DSC 129 
#define  BLE_GATT_REGISTER_OP_SVC 128 
 int BLE_UUID_STR_LEN ; 
 int /*<<< orphan*/  DEBUG ; 
 int /*<<< orphan*/  MODLOG_DFLT (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ble_uuid_to_str (int /*<<< orphan*/ ,char*) ; 

void
gatt_svr_register_cb(struct ble_gatt_register_ctxt *ctxt, void *arg)
{
    char buf[BLE_UUID_STR_LEN];

    switch (ctxt->op) {
    case BLE_GATT_REGISTER_OP_SVC:
        MODLOG_DFLT(DEBUG, "registered service %s with handle=%d\n",
                    ble_uuid_to_str(ctxt->svc.svc_def->uuid, buf),
                    ctxt->svc.handle);
        break;

    case BLE_GATT_REGISTER_OP_CHR:
        MODLOG_DFLT(DEBUG, "registering characteristic %s with "
                    "def_handle=%d val_handle=%d\n",
                    ble_uuid_to_str(ctxt->chr.chr_def->uuid, buf),
                    ctxt->chr.def_handle,
                    ctxt->chr.val_handle);
        break;

    case BLE_GATT_REGISTER_OP_DSC:
        MODLOG_DFLT(DEBUG, "registering descriptor %s with handle=%d\n",
                    ble_uuid_to_str(ctxt->dsc.dsc_def->uuid, buf),
                    ctxt->dsc.handle);
        break;

    default:
        assert(0);
        break;
    }
}