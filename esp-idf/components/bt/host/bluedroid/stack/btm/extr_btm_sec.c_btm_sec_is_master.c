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
struct TYPE_5__ {int /*<<< orphan*/  bd_addr; } ;
typedef  TYPE_1__ tBTM_SEC_DEV_REC ;
struct TYPE_6__ {scalar_t__ link_role; } ;
typedef  TYPE_2__ tACL_CONN ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ BTM_ROLE_MASTER ; 
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 TYPE_2__* btm_bda_to_acl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOLEAN btm_sec_is_master(tBTM_SEC_DEV_REC *p_dev_rec)
{
    tACL_CONN *p = btm_bda_to_acl(p_dev_rec->bd_addr, BT_TRANSPORT_BR_EDR);
    return (p && (p->link_role == BTM_ROLE_MASTER));
}