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
struct TYPE_9__ {TYPE_2__* p_rcb; } ;
typedef  TYPE_3__ tBTA_GATTC_CLCB ;
struct TYPE_7__ {int /*<<< orphan*/  congested; int /*<<< orphan*/  conn_id; } ;
struct TYPE_10__ {TYPE_1__ congest; } ;
typedef  TYPE_4__ tBTA_GATTC ;
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_8__ {int /*<<< orphan*/  (* p_cback ) (int /*<<< orphan*/ ,TYPE_4__*) ;} ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_GATTC_CONGEST_EVT ; 
 TYPE_3__* bta_gattc_find_clcb_by_conn_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static void bta_gattc_cong_cback (UINT16 conn_id, BOOLEAN congested)
{
    tBTA_GATTC_CLCB *p_clcb;
    tBTA_GATTC cb_data;

    if ((p_clcb = bta_gattc_find_clcb_by_conn_id(conn_id)) != NULL) {
        if (p_clcb->p_rcb->p_cback) {
            cb_data.congest.conn_id = conn_id;
            cb_data.congest.congested = congested;

            (*p_clcb->p_rcb->p_cback)(BTA_GATTC_CONGEST_EVT, &cb_data);
        }
    }
}