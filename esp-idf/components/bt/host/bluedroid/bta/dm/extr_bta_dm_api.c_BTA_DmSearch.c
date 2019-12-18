#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTA_SERVICE_MASK ;
typedef  int /*<<< orphan*/  tBTA_DM_SEARCH_CBACK ;
typedef  int /*<<< orphan*/  tBTA_DM_INQ ;
struct TYPE_5__ {int /*<<< orphan*/  event; } ;
struct TYPE_6__ {int /*<<< orphan*/  rs_res; int /*<<< orphan*/ * p_cback; int /*<<< orphan*/  services; int /*<<< orphan*/  inq_params; TYPE_1__ hdr; } ;
typedef  TYPE_2__ tBTA_DM_API_SEARCH ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DM_API_SEARCH_EVT ; 
 int /*<<< orphan*/  BTA_DM_RS_NONE ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ osi_malloc (int) ; 

void BTA_DmSearch(tBTA_DM_INQ *p_dm_inq, tBTA_SERVICE_MASK services, tBTA_DM_SEARCH_CBACK *p_cback)
{

    tBTA_DM_API_SEARCH    *p_msg;

    if ((p_msg = (tBTA_DM_API_SEARCH *) osi_malloc(sizeof(tBTA_DM_API_SEARCH))) != NULL) {
        memset(p_msg, 0, sizeof(tBTA_DM_API_SEARCH));

        p_msg->hdr.event = BTA_DM_API_SEARCH_EVT;
        memcpy(&p_msg->inq_params, p_dm_inq, sizeof(tBTA_DM_INQ));
        p_msg->services = services;
        p_msg->p_cback = p_cback;
        p_msg->rs_res  = BTA_DM_RS_NONE;
        bta_sys_sendmsg(p_msg);
    }

}