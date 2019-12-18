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
struct TYPE_3__ {int /*<<< orphan*/  bond_type; } ;
typedef  TYPE_1__ tBTM_SEC_DEV_REC ;
typedef  int /*<<< orphan*/  tBTM_BOND_TYPE ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BOND_TYPE_UNKNOWN ; 
 TYPE_1__* btm_find_dev (int /*<<< orphan*/ ) ; 

tBTM_BOND_TYPE btm_get_bond_type_dev(BD_ADDR bd_addr)
{
    tBTM_SEC_DEV_REC *p_dev_rec = btm_find_dev(bd_addr);

    if (p_dev_rec == NULL) {
        return BOND_TYPE_UNKNOWN;
    }

    return p_dev_rec->bond_type;
}