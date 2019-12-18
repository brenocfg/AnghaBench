#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * p_esco_cback; } ;
struct TYPE_7__ {scalar_t__ state; scalar_t__ hci_handle; TYPE_1__ esco; } ;
typedef  TYPE_3__ tSCO_CONN ;
typedef  int /*<<< orphan*/  tBTM_STATUS ;
typedef  size_t UINT16 ;
struct TYPE_6__ {TYPE_3__* sco_db; } ;
struct TYPE_8__ {TYPE_2__ sco_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_CMD_STARTED ; 
 scalar_t__ BTM_INVALID_HCI_HANDLE ; 
 size_t BTM_MAX_SCO_LINKS ; 
 int /*<<< orphan*/  BTM_NO_RESOURCES ; 
 int /*<<< orphan*/  BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_UNKNOWN_ADDR ; 
 int /*<<< orphan*/  HCI_ERR_PEER_USER ; 
 size_t SCO_ST_DISCONNECTING ; 
 scalar_t__ SCO_ST_PEND_UNPARK ; 
 scalar_t__ SCO_ST_UNUSED ; 
 TYPE_4__ btm_cb ; 
 int /*<<< orphan*/  btsnd_hcic_disconnect (scalar_t__,int /*<<< orphan*/ ) ; 

tBTM_STATUS BTM_RemoveSco (UINT16 sco_inx)
{
#if (BTM_MAX_SCO_LINKS>0)
    tSCO_CONN   *p = &btm_cb.sco_cb.sco_db[sco_inx];
    UINT16       tempstate;

    /* Validity check */
    if ((sco_inx >= BTM_MAX_SCO_LINKS) || (p->state == SCO_ST_UNUSED)) {
        return (BTM_UNKNOWN_ADDR);
    }

    /* If no HCI handle, simply drop the connection and return */
    if (p->hci_handle == BTM_INVALID_HCI_HANDLE || p->state == SCO_ST_PEND_UNPARK) {
        p->hci_handle = BTM_INVALID_HCI_HANDLE;
        p->state = SCO_ST_UNUSED;
        p->esco.p_esco_cback = NULL;    /* Deregister the eSCO event callback */
        return (BTM_SUCCESS);
    }

    tempstate = p->state;
    p->state = SCO_ST_DISCONNECTING;

    if (!btsnd_hcic_disconnect (p->hci_handle, HCI_ERR_PEER_USER)) {
        p->state = tempstate;
        return (BTM_NO_RESOURCES);
    }

    return (BTM_CMD_STARTED);
#else
    return (BTM_NO_RESOURCES);
#endif
}