#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ ** peer_lmp_features; } ;
typedef  TYPE_1__ tACL_CONN ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 size_t HCI_EXT_FEATURES_PAGE_0 ; 
 TYPE_1__* btm_bda_to_acl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

UINT8 *BTM_ReadAllRemoteFeatures (BD_ADDR addr)
{
    tACL_CONN        *p = btm_bda_to_acl(addr, BT_TRANSPORT_BR_EDR);
    BTM_TRACE_DEBUG ("BTM_ReadAllRemoteFeatures\n");
    if (p == NULL) {
        return (NULL);
    }

    return (p->peer_lmp_features[HCI_EXT_FEATURES_PAGE_0]);
}