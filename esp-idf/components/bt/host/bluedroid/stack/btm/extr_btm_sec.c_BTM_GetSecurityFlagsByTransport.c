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
typedef  scalar_t__ tBT_TRANSPORT ;
struct TYPE_3__ {int sec_flags; } ;
typedef  TYPE_1__ tBTM_SEC_DEV_REC ;
typedef  scalar_t__ UINT8 ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_TRACE_ERROR (char*) ; 
 scalar_t__ BT_TRANSPORT_BR_EDR ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* btm_find_dev (int /*<<< orphan*/ ) ; 

BOOLEAN BTM_GetSecurityFlagsByTransport (BD_ADDR bd_addr, UINT8 *p_sec_flags,
        tBT_TRANSPORT transport)
{
    tBTM_SEC_DEV_REC *p_dev_rec;

    if ((p_dev_rec = btm_find_dev (bd_addr)) != NULL) {
        if (transport == BT_TRANSPORT_BR_EDR) {
            *p_sec_flags = (UINT8) p_dev_rec->sec_flags;
        } else {
            *p_sec_flags = (UINT8) (p_dev_rec->sec_flags >> 8);
        }

        return (TRUE);
    }
    BTM_TRACE_ERROR ("BTM_GetSecurityFlags false\n");
    return (FALSE);
}