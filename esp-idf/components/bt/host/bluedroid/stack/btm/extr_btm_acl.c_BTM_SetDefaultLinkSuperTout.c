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
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_2__ {int /*<<< orphan*/  btm_def_link_super_tout; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*) ; 
 TYPE_1__ btm_cb ; 

void BTM_SetDefaultLinkSuperTout (UINT16 timeout)
{
    BTM_TRACE_DEBUG ("BTM_SetDefaultLinkSuperTout\n");
    btm_cb.btm_def_link_super_tout = timeout;
}