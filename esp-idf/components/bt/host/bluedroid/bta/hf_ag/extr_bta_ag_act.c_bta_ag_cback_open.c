#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTA_AG_STATUS ;
struct TYPE_12__ {size_t conn_service; int /*<<< orphan*/  peer_addr; int /*<<< orphan*/  app_id; } ;
typedef  TYPE_3__ tBTA_AG_SCB ;
struct TYPE_11__ {int /*<<< orphan*/  app_id; int /*<<< orphan*/  handle; } ;
struct TYPE_13__ {int /*<<< orphan*/  bd_addr; int /*<<< orphan*/  service_id; int /*<<< orphan*/  status; TYPE_2__ hdr; } ;
typedef  TYPE_4__ tBTA_AG_OPEN ;
struct TYPE_10__ {int /*<<< orphan*/  bd_addr; } ;
struct TYPE_14__ {TYPE_1__ api_open; } ;
typedef  TYPE_5__ tBTA_AG_DATA ;
typedef  int /*<<< orphan*/  tBTA_AG ;
struct TYPE_15__ {int /*<<< orphan*/  (* p_cback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_AG_OPEN_EVT ; 
 int /*<<< orphan*/  bdcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_9__ bta_ag_cb ; 
 int /*<<< orphan*/  bta_ag_scb_to_idx (TYPE_3__*) ; 
 int /*<<< orphan*/ * bta_ag_svc_id ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bta_ag_cback_open(tBTA_AG_SCB *p_scb, tBTA_AG_DATA *p_data, tBTA_AG_STATUS status)
{
    tBTA_AG_OPEN    open;
    /* call app callback with open event */
    open.hdr.handle = bta_ag_scb_to_idx(p_scb);
    open.hdr.app_id = p_scb->app_id;
    open.status = status;
    open.service_id = bta_ag_svc_id[p_scb->conn_service];
    if (p_data) {
        /* if p_data is provided then we need to pick the bd address from the open api structure */
        bdcpy(open.bd_addr, p_data->api_open.bd_addr);
    } else {
        bdcpy(open.bd_addr, p_scb->peer_addr);
    }
    (*bta_ag_cb.p_cback)(BTA_AG_OPEN_EVT, (tBTA_AG *) &open);
}