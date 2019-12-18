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
typedef  int /*<<< orphan*/  tBTM_STATUS ;
struct TYPE_3__ {int /*<<< orphan*/  lmp_subversion; int /*<<< orphan*/  manufacturer; int /*<<< orphan*/  lmp_version; } ;
typedef  TYPE_1__ tACL_CONN ;
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  BTM_UNKNOWN_ADDR ; 
 int /*<<< orphan*/  BT_TRANSPORT_BR_EDR ; 
 TYPE_1__* btm_bda_to_acl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tBTM_STATUS BTM_ReadRemoteVersion (BD_ADDR addr, UINT8 *lmp_version,
                                   UINT16 *manufacturer, UINT16 *lmp_sub_version)
{
    tACL_CONN        *p = btm_bda_to_acl(addr, BT_TRANSPORT_BR_EDR);
    BTM_TRACE_DEBUG ("BTM_ReadRemoteVersion\n");
    if (p == NULL) {
        return (BTM_UNKNOWN_ADDR);
    }

    if (lmp_version) {
        *lmp_version = p->lmp_version;
    }

    if (manufacturer) {
        *manufacturer = p->manufacturer;
    }

    if (lmp_sub_version) {
        *lmp_sub_version = p->lmp_subversion;
    }

    return (BTM_SUCCESS);
}