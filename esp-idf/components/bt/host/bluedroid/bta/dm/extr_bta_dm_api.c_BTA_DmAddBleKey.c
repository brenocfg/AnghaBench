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
typedef  int /*<<< orphan*/  tBTA_LE_KEY_VALUE ;
typedef  int /*<<< orphan*/  tBTA_LE_KEY_TYPE ;
struct TYPE_5__ {int /*<<< orphan*/  event; } ;
struct TYPE_6__ {int /*<<< orphan*/  blekey; int /*<<< orphan*/  bd_addr; int /*<<< orphan*/  key_type; TYPE_1__ hdr; } ;
typedef  TYPE_2__ tBTA_DM_API_ADD_BLEKEY ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTA_DM_API_ADD_BLEKEY_EVT ; 
 int /*<<< orphan*/  bdcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bta_sys_sendmsg (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ osi_malloc (int) ; 

void BTA_DmAddBleKey (BD_ADDR bd_addr, tBTA_LE_KEY_VALUE *p_le_key, tBTA_LE_KEY_TYPE key_type)
{
    tBTA_DM_API_ADD_BLEKEY *p_msg;

    if ((p_msg = (tBTA_DM_API_ADD_BLEKEY *) osi_malloc(sizeof(tBTA_DM_API_ADD_BLEKEY))) != NULL) {
        memset (p_msg, 0, sizeof(tBTA_DM_API_ADD_BLEKEY));

        p_msg->hdr.event = BTA_DM_API_ADD_BLEKEY_EVT;
        p_msg->key_type = key_type;
        bdcpy(p_msg->bd_addr, bd_addr);
        memcpy(&p_msg->blekey, p_le_key, sizeof(tBTA_LE_KEY_VALUE));

        bta_sys_sendmsg(p_msg);
    }

}