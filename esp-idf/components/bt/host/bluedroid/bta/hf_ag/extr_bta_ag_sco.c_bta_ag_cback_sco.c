#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  app_id; } ;
typedef  TYPE_1__ tBTA_AG_SCB ;
struct TYPE_7__ {int /*<<< orphan*/  app_id; int /*<<< orphan*/  handle; } ;
typedef  TYPE_2__ tBTA_AG_HDR ;
typedef  int /*<<< orphan*/  tBTA_AG ;
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_8__ {int /*<<< orphan*/  (* p_cback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_5__ bta_ag_cb ; 
 int /*<<< orphan*/  bta_ag_scb_to_idx (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bta_ag_cback_sco(tBTA_AG_SCB *p_scb, UINT8 event)
{
    tBTA_AG_HDR    sco;

    sco.handle = bta_ag_scb_to_idx(p_scb);
    sco.app_id = p_scb->app_id;

    /* call close cback */
    (*bta_ag_cb.p_cback)(event, (tBTA_AG *) &sco);
}