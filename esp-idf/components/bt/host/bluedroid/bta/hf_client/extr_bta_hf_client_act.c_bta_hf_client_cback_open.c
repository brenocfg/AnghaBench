#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTA_HF_CLIENT_STATUS ;
struct TYPE_11__ {int /*<<< orphan*/  bd_addr; int /*<<< orphan*/  status; } ;
typedef  TYPE_3__ tBTA_HF_CLIENT_OPEN ;
struct TYPE_9__ {int /*<<< orphan*/  bd_addr; } ;
struct TYPE_12__ {TYPE_1__ api_open; } ;
typedef  TYPE_4__ tBTA_HF_CLIENT_DATA ;
typedef  int /*<<< orphan*/  evt ;
struct TYPE_10__ {int /*<<< orphan*/  peer_addr; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* p_cback ) (int /*<<< orphan*/ ,TYPE_3__*) ;TYPE_2__ scb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_HF_CLIENT_OPEN_EVT ; 
 int /*<<< orphan*/  bdcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_8__ bta_hf_client_cb ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static void bta_hf_client_cback_open(tBTA_HF_CLIENT_DATA *p_data, tBTA_HF_CLIENT_STATUS status)
{
    tBTA_HF_CLIENT_OPEN evt;

    memset(&evt, 0, sizeof(evt));

    /* call app callback with open event */
    evt.status = status;
    if (p_data) {
        /* if p_data is provided then we need to pick the bd address from the open api structure */
        bdcpy(evt.bd_addr, p_data->api_open.bd_addr);
    } else {
        bdcpy(evt.bd_addr, bta_hf_client_cb.scb.peer_addr);
    }

    (*bta_hf_client_cb.p_cback)(BTA_HF_CLIENT_OPEN_EVT, &evt);
}