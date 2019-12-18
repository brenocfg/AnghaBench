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
struct TYPE_4__ {int /*<<< orphan*/  event; } ;
struct TYPE_5__ {int /*<<< orphan*/  r; int /*<<< orphan*/  c; int /*<<< orphan*/  accept; int /*<<< orphan*/  bd_addr; TYPE_1__ hdr; } ;
typedef  TYPE_2__ tBTA_DM_CI_RMT_OOB ;
typedef  int /*<<< orphan*/  BT_OCTET16 ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DM_CI_RMT_OOB_EVT ; 
 int /*<<< orphan*/  BT_OCTET16_LEN ; 
 int /*<<< orphan*/  bdcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ osi_malloc (int) ; 

void bta_dm_ci_rmt_oob(BOOLEAN accept, BD_ADDR bd_addr, BT_OCTET16 c, BT_OCTET16 r)
{
    tBTA_DM_CI_RMT_OOB    *p_msg;

    if ((p_msg = (tBTA_DM_CI_RMT_OOB *) osi_malloc(sizeof(tBTA_DM_CI_RMT_OOB))) != NULL) {
        p_msg->hdr.event = BTA_DM_CI_RMT_OOB_EVT;
        bdcpy(p_msg->bd_addr, bd_addr);
        p_msg->accept    = accept;
        memcpy(p_msg->c, c, BT_OCTET16_LEN);
        memcpy(p_msg->r, r, BT_OCTET16_LEN);
        bta_sys_sendmsg(p_msg);
    }
}