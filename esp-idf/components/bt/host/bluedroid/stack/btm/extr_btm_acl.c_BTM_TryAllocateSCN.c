#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT8 ;
struct TYPE_2__ {scalar_t__* btm_scn; } ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int BTM_MAX_SCN ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 TYPE_1__ btm_cb ; 

BOOLEAN BTM_TryAllocateSCN(UINT8 scn)
{
    if (scn >= BTM_MAX_SCN) {
        return FALSE;
    }

    /* check if this port is available */
    if (!btm_cb.btm_scn[scn - 1]) {
        btm_cb.btm_scn[scn - 1] = TRUE;
        return TRUE;
    }

    return (FALSE);     /* Port was busy */
}