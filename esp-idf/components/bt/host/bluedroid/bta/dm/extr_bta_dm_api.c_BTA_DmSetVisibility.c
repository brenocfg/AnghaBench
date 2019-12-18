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
typedef  int /*<<< orphan*/  tBTA_DM_DISC ;
typedef  int /*<<< orphan*/  tBTA_DM_CONN ;
struct TYPE_4__ {int /*<<< orphan*/  event; } ;
struct TYPE_5__ {void* conn_paired_only; void* pair_mode; int /*<<< orphan*/  conn_mode; int /*<<< orphan*/  disc_mode; TYPE_1__ hdr; } ;
typedef  TYPE_2__ tBTA_DM_API_SET_VISIBILITY ;
typedef  void* UINT8 ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DM_API_SET_VISIBILITY_EVT ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_2__*) ; 
 scalar_t__ osi_malloc (int) ; 

void BTA_DmSetVisibility(tBTA_DM_DISC disc_mode, tBTA_DM_CONN conn_mode, UINT8 pairable_mode, UINT8 conn_filter )
{

    tBTA_DM_API_SET_VISIBILITY    *p_msg;

    if ((p_msg = (tBTA_DM_API_SET_VISIBILITY *) osi_malloc(sizeof(tBTA_DM_API_SET_VISIBILITY))) != NULL) {
        p_msg->hdr.event = BTA_DM_API_SET_VISIBILITY_EVT;
        p_msg->disc_mode = disc_mode;
        p_msg->conn_mode = conn_mode;
        p_msg->pair_mode = pairable_mode;
        p_msg->conn_paired_only = conn_filter;


        bta_sys_sendmsg(p_msg);
    }


}