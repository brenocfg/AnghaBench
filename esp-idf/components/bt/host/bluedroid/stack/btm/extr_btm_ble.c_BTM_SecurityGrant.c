#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  tSMP_STATUS ;
typedef  scalar_t__ UINT8 ;
typedef  int /*<<< orphan*/  BD_ADDR ;

/* Variables and functions */
 scalar_t__ BTM_SUCCESS ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  SMP_REPEATED_ATTEMPTS ; 
 int /*<<< orphan*/  SMP_SUCCESS ; 
 int /*<<< orphan*/  SMP_SecurityGrant (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void BTM_SecurityGrant(BD_ADDR bd_addr, UINT8 res)
{
#if SMP_INCLUDED == TRUE
    tSMP_STATUS res_smp = (res == BTM_SUCCESS) ? SMP_SUCCESS : SMP_REPEATED_ATTEMPTS;
    BTM_TRACE_DEBUG ("BTM_SecurityGrant");
    SMP_SecurityGrant(bd_addr, res_smp);
#endif
}