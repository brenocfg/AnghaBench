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
struct TYPE_5__ {scalar_t__* name; TYPE_1__ hdr; } ;
typedef  TYPE_2__ tBTA_DM_API_SET_NAME ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_STRNCPY_S (char*,int,char const*,int) ; 
 int BD_NAME_LEN ; 
 int /*<<< orphan*/  BTA_DM_API_SET_NAME_EVT ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_2__*) ; 
 scalar_t__ osi_malloc (int) ; 

void BTA_DmSetDeviceName(const char *p_name)
{

    tBTA_DM_API_SET_NAME    *p_msg;

    if ((p_msg = (tBTA_DM_API_SET_NAME *) osi_malloc(sizeof(tBTA_DM_API_SET_NAME))) != NULL) {
        p_msg->hdr.event = BTA_DM_API_SET_NAME_EVT;
        /* truncate the name if needed */
        BCM_STRNCPY_S((char *)p_msg->name, sizeof(p_msg->name), p_name, BD_NAME_LEN - 1);
        p_msg->name[BD_NAME_LEN - 1] = 0;

        bta_sys_sendmsg(p_msg);
    }
}