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

/* Variables and functions */
 int BTM_MAX_SCN ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*) ; 
 scalar_t__ TRUE ; 
 TYPE_1__ btm_cb ; 

UINT8 BTM_AllocateSCN(void)
{
    UINT8   x;
    BTM_TRACE_DEBUG ("BTM_AllocateSCN\n");
    for (x = 1; x < BTM_MAX_SCN; x++) {
        if (!btm_cb.btm_scn[x - 1]) {
            btm_cb.btm_scn[x - 1] = TRUE;
            return x;
        }
    }
    return (0);    /* No free ports */
}