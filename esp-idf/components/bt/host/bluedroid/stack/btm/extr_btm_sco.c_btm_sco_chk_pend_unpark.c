#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  bd_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  setup; TYPE_1__ data; } ;
struct TYPE_9__ {scalar_t__ state; TYPE_2__ esco; } ;
typedef  TYPE_4__ tSCO_CONN ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_8__ {int /*<<< orphan*/  desired_sco_mode; TYPE_4__* sco_db; } ;
struct TYPE_10__ {TYPE_3__ sco_cb; } ;

/* Variables and functions */
 scalar_t__ BTM_CMD_STARTED ; 
 scalar_t__ BTM_GetHCIConnHandle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ BTM_MAX_SCO_LINKS ; 
 int /*<<< orphan*/  BTM_TRACE_API (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 scalar_t__ SCO_ST_CONNECTING ; 
 scalar_t__ SCO_ST_PEND_UNPARK ; 
 TYPE_5__ btm_cb ; 
 scalar_t__ btm_send_connect_request (scalar_t__,int /*<<< orphan*/ *) ; 

void btm_sco_chk_pend_unpark (UINT8 hci_status, UINT16 hci_handle)
{
#if (BTM_MAX_SCO_LINKS>0)
    UINT16      xx;
    UINT16      acl_handle;
    tSCO_CONN   *p = &btm_cb.sco_cb.sco_db[0];

    for (xx = 0; xx < BTM_MAX_SCO_LINKS; xx++, p++) {
        if ((p->state == SCO_ST_PEND_UNPARK) &&
                ((acl_handle = BTM_GetHCIConnHandle (p->esco.data.bd_addr, BT_TRANSPORT_BR_EDR)) == hci_handle))

        {
            BTM_TRACE_API("btm_sco_chk_pend_unpark -> (e)SCO Link for ACL handle 0x%04x, Desired Type %d, hci_status 0x%02x",
                          acl_handle, btm_cb.sco_cb.desired_sco_mode, hci_status);

            if ((btm_send_connect_request(acl_handle, &p->esco.setup)) == BTM_CMD_STARTED) {
                p->state = SCO_ST_CONNECTING;
            }
        }
    }
#endif  // BTM_MAX_SCO_LINKS
}