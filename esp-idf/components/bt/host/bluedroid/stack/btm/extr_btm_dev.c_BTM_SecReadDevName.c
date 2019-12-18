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
struct TYPE_3__ {scalar_t__ sec_bd_name; } ;
typedef  TYPE_1__ tBTM_SEC_DEV_REC ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 TYPE_1__* btm_find_dev (int /*<<< orphan*/ ) ; 

char *BTM_SecReadDevName (BD_ADDR bd_addr)
{
    char *p_name = NULL;
    tBTM_SEC_DEV_REC *p_srec;

    if ((p_srec = btm_find_dev(bd_addr)) != NULL) {
        p_name = (char *)p_srec->sec_bd_name;
    }

    return (p_name);
}