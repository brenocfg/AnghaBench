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
typedef  int /*<<< orphan*/  tBTM_ESCO_PARAMS ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  size_t UINT16 ;
struct TYPE_9__ {TYPE_3__* sco_db; } ;
struct TYPE_10__ {TYPE_4__ sco_cb; } ;
struct TYPE_6__ {int /*<<< orphan*/  bd_addr; } ;
struct TYPE_7__ {TYPE_1__ data; } ;
struct TYPE_8__ {scalar_t__ state; TYPE_2__ esco; } ;

/* Variables and functions */
 size_t BTM_MAX_SCO_LINKS ; 
 scalar_t__ SCO_ST_W4_CONN_RSP ; 
 TYPE_5__ btm_cb ; 
 int /*<<< orphan*/  btm_esco_conn_rsp (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void BTM_EScoConnRsp (UINT16 sco_inx, UINT8 hci_status, tBTM_ESCO_PARAMS *p_parms)
{
#if (BTM_MAX_SCO_LINKS>0)
    if (sco_inx < BTM_MAX_SCO_LINKS &&
            btm_cb.sco_cb.sco_db[sco_inx].state == SCO_ST_W4_CONN_RSP) {
        btm_esco_conn_rsp(sco_inx, hci_status,
                          btm_cb.sco_cb.sco_db[sco_inx].esco.data.bd_addr,
                          p_parms);
    }
#endif
}