#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tBTM_STATUS ;
typedef  int /*<<< orphan*/  tBTM_CMPL_CB ;
struct TYPE_6__ {int /*<<< orphan*/  hci_handle; } ;
typedef  TYPE_2__ tACL_CONN ;
struct TYPE_5__ {int /*<<< orphan*/ * p_lnk_qual_cmpl_cb; int /*<<< orphan*/  lnk_quality_timer; } ;
struct TYPE_7__ {TYPE_1__ devcb; } ;
typedef  int /*<<< orphan*/ * BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_BUSY ; 
 int /*<<< orphan*/  BTM_CMD_STARTED ; 
 int /*<<< orphan*/  BTM_DEV_REPLY_TIMEOUT ; 
 int /*<<< orphan*/  BTM_NO_RESOURCES ; 
 int /*<<< orphan*/  BTM_TRACE_API (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTM_UNKNOWN_ADDR ; 
 int /*<<< orphan*/  BTU_TTYPE_BTM_ACL ; 
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 TYPE_2__* btm_bda_to_acl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__ btm_cb ; 
 int /*<<< orphan*/  btsnd_hcic_get_link_quality (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btu_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btu_stop_timer (int /*<<< orphan*/ *) ; 

tBTM_STATUS BTM_ReadLinkQuality (BD_ADDR remote_bda, tBTM_CMPL_CB *p_cb)
{
    tACL_CONN   *p;

    BTM_TRACE_API ("BTM_ReadLinkQuality: RemBdAddr: %02x%02x%02x%02x%02x%02x\n",
                   remote_bda[0], remote_bda[1], remote_bda[2],
                   remote_bda[3], remote_bda[4], remote_bda[5]);

    /* If someone already waiting on the version, do not allow another */
    if (btm_cb.devcb.p_lnk_qual_cmpl_cb) {
        return (BTM_BUSY);
    }

    p = btm_bda_to_acl(remote_bda, BT_TRANSPORT_BR_EDR);
    if (p != (tACL_CONN *)NULL) {
        btu_start_timer (&btm_cb.devcb.lnk_quality_timer, BTU_TTYPE_BTM_ACL,
                         BTM_DEV_REPLY_TIMEOUT);
        btm_cb.devcb.p_lnk_qual_cmpl_cb = p_cb;

        if (!btsnd_hcic_get_link_quality (p->hci_handle)) {
            btu_stop_timer (&btm_cb.devcb.lnk_quality_timer);
            btm_cb.devcb.p_lnk_qual_cmpl_cb = NULL;
            return (BTM_NO_RESOURCES);
        } else {
            return (BTM_CMD_STARTED);
        }
    }

    /* If here, no BD Addr found */
    return (BTM_UNKNOWN_ADDR);
}