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
struct TYPE_5__ {int /*<<< orphan*/  remote_addr; int /*<<< orphan*/ * add_wl_cb; int /*<<< orphan*/  addr_type; int /*<<< orphan*/  add_remove; TYPE_1__ hdr; } ;
typedef  TYPE_2__ tBTA_DM_API_UPDATE_WHITE_LIST ;
typedef  int /*<<< orphan*/  tBTA_ADD_WHITELIST_CBACK ;
typedef  int /*<<< orphan*/  tBLE_ADDR_TYPE ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DM_API_UPDATE_WHITE_LIST_EVT ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ osi_malloc (int) ; 

void BTA_DmUpdateWhiteList(BOOLEAN add_remove,  BD_ADDR remote_addr, tBLE_ADDR_TYPE addr_type, tBTA_ADD_WHITELIST_CBACK *add_wl_cb)
{
    tBTA_DM_API_UPDATE_WHITE_LIST *p_msg;
    if ((p_msg = (tBTA_DM_API_UPDATE_WHITE_LIST *)osi_malloc(sizeof(tBTA_DM_API_UPDATE_WHITE_LIST))) != NULL) {
        p_msg->hdr.event = BTA_DM_API_UPDATE_WHITE_LIST_EVT;
        p_msg->add_remove = add_remove;
        p_msg->addr_type = addr_type;
        p_msg->add_wl_cb = add_wl_cb;
        memcpy(p_msg->remote_addr, remote_addr, sizeof(BD_ADDR));

        bta_sys_sendmsg(p_msg);
    }
}