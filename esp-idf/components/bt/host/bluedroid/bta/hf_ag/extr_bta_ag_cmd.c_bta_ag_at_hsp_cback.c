#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  app_id; int /*<<< orphan*/  handle; } ;
struct TYPE_9__ {size_t num; scalar_t__* str; TYPE_1__ hdr; } ;
typedef  TYPE_2__ tBTA_AG_VAL ;
struct TYPE_10__ {int /*<<< orphan*/  app_id; } ;
typedef  TYPE_3__ tBTA_AG_SCB ;
typedef  int /*<<< orphan*/  tBTA_AG ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  size_t UINT16 ;
struct TYPE_11__ {int /*<<< orphan*/  (* p_cback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  scalar_t__ INT16 ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,size_t,int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  BCM_STRNCPY_S (scalar_t__*,int,char*,size_t) ; 
 size_t BTA_AG_AT_MAX_LEN ; 
 TYPE_6__ bta_ag_cb ; 
 int /*<<< orphan*/ * bta_ag_hsp_cb_evt ; 
 int /*<<< orphan*/  bta_ag_scb_to_idx (TYPE_3__*) ; 
 int /*<<< orphan*/  bta_ag_send_ok (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void bta_ag_at_hsp_cback(tBTA_AG_SCB *p_scb, UINT16 cmd, UINT8 arg_type,
                                char *p_arg, INT16 int_arg)
{
    tBTA_AG_VAL val;
    APPL_TRACE_DEBUG("AT cmd:%d arg_type:%d arg:%d arg:%s", cmd, arg_type, int_arg, p_arg);

    /* send OK */
    bta_ag_send_ok(p_scb);
    val.hdr.handle = bta_ag_scb_to_idx(p_scb);
    val.hdr.app_id = p_scb->app_id;
    val.num = (UINT16) int_arg;
    BCM_STRNCPY_S(val.str, sizeof(val.str), p_arg, BTA_AG_AT_MAX_LEN);
    val.str[BTA_AG_AT_MAX_LEN] = 0;
    /* call callback with event */
    (*bta_ag_cb.p_cback)(bta_ag_hsp_cb_evt[cmd], (tBTA_AG *) &val);
}