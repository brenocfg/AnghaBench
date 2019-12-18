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
struct TYPE_3__ {size_t** peer_lmp_features; } ;
typedef  TYPE_1__ tACL_CONN ;
typedef  size_t UINT8 ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*,size_t) ; 
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 size_t HCI_EXT_FEATURES_PAGE_MAX ; 
 TYPE_1__* btm_bda_to_acl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

UINT8 *BTM_ReadRemoteExtendedFeatures (BD_ADDR addr, UINT8 page_number)
{
    tACL_CONN        *p = btm_bda_to_acl(addr, BT_TRANSPORT_BR_EDR);
    BTM_TRACE_DEBUG ("BTM_ReadRemoteExtendedFeatures\n");
    if (p == NULL) {
        return (NULL);
    }

    if (page_number > HCI_EXT_FEATURES_PAGE_MAX) {
        BTM_TRACE_ERROR("Warning: BTM_ReadRemoteExtendedFeatures page %d unknown\n", page_number);
        return NULL;
    }

    return (p->peer_lmp_features[page_number]);
}