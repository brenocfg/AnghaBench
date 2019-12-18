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
typedef  size_t UINT16 ;
struct TYPE_9__ {TYPE_3__* sco_db; } ;
struct TYPE_10__ {TYPE_4__ sco_cb; } ;
struct TYPE_6__ {int /*<<< orphan*/  bd_addr; } ;
struct TYPE_7__ {TYPE_1__ data; } ;
struct TYPE_8__ {TYPE_2__ esco; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_ERR_HOST_REJECT_RESOURCES ; 
 TYPE_5__ btm_cb ; 
 int /*<<< orphan*/  btm_esco_conn_rsp (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void btm_reject_sco_link( UINT16 sco_inx )
{
    btm_esco_conn_rsp(sco_inx, HCI_ERR_HOST_REJECT_RESOURCES,
                      btm_cb.sco_cb.sco_db[sco_inx].esco.data.bd_addr, NULL);
}