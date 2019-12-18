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
struct TYPE_2__ {int /*<<< orphan*/ * btm_scn; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int BTM_MAX_SCN ; 
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__ btm_cb ; 

BOOLEAN BTM_FreeSCN(UINT8 scn)
{
    BTM_TRACE_DEBUG ("BTM_FreeSCN \n");
    if (scn <= BTM_MAX_SCN) {
        btm_cb.btm_scn[scn - 1] = FALSE;
        return (TRUE);
    } else {
        return (FALSE);    /* Illegal SCN passed in */
    }
    return (FALSE);
}