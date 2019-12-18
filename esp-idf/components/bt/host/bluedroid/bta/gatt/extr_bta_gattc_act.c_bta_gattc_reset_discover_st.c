#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTA_GATT_STATUS ;
typedef  int /*<<< orphan*/  tBTA_GATTC_SERV ;
struct TYPE_4__ {TYPE_2__* clcb; } ;
typedef  TYPE_1__ tBTA_GATTC_CB ;
typedef  size_t UINT8 ;
struct TYPE_5__ {int /*<<< orphan*/  status; int /*<<< orphan*/ * p_srcb; } ;

/* Variables and functions */
 size_t BTA_GATTC_CLCB_MAX ; 
 int /*<<< orphan*/  BTA_GATTC_DISCOVER_CMPL_EVT ; 
 TYPE_1__ bta_gattc_cb ; 
 int /*<<< orphan*/  bta_gattc_sm_execute (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void bta_gattc_reset_discover_st(tBTA_GATTC_SERV *p_srcb, tBTA_GATT_STATUS status)
{
    tBTA_GATTC_CB   *p_cb = &bta_gattc_cb;
    UINT8 i;

    for (i = 0; i < BTA_GATTC_CLCB_MAX; i ++) {
        if (p_cb->clcb[i].p_srcb == p_srcb) {
            p_cb->clcb[i].status = status;
            bta_gattc_sm_execute(&p_cb->clcb[i], BTA_GATTC_DISCOVER_CMPL_EVT, NULL);
        }
    }
}