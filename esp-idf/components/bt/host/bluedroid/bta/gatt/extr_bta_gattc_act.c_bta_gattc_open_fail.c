#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTA_GATTC_DATA ;
struct TYPE_4__ {int /*<<< orphan*/  transport; int /*<<< orphan*/  bta_conn_id; int /*<<< orphan*/  bda; int /*<<< orphan*/  p_rcb; } ;
typedef  TYPE_1__ tBTA_GATTC_CLCB ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_GATT_ERROR ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bta_gattc_clcb_dealloc (TYPE_1__*) ; 
 int /*<<< orphan*/  bta_gattc_send_open_cback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void bta_gattc_open_fail(tBTA_GATTC_CLCB *p_clcb, tBTA_GATTC_DATA *p_data)
{
    UNUSED(p_data);

    bta_gattc_send_open_cback(p_clcb->p_rcb,
                              BTA_GATT_ERROR,
                              p_clcb->bda,
                              p_clcb->bta_conn_id,
                              p_clcb->transport,
                              0);
    /* open failure, remove clcb */
    bta_gattc_clcb_dealloc(p_clcb);
}