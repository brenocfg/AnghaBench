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
typedef  int /*<<< orphan*/  FreeProc ;

/* Variables and functions */
 int /*<<< orphan*/ * Dir_Destroy ; 
 int /*<<< orphan*/  Lst_Destroy (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ defIncPath ; 
 scalar_t__ free ; 
 scalar_t__ includes ; 
 scalar_t__ parseIncPath ; 
 scalar_t__ sysIncPath ; 
 scalar_t__ targCmds ; 
 scalar_t__ targets ; 

void
Parse_End(void)
{
#ifdef CLEANUP
    Lst_Destroy(targCmds, (FreeProc *)free);
    if (targets)
	Lst_Destroy(targets, NULL);
    Lst_Destroy(defIncPath, Dir_Destroy);
    Lst_Destroy(sysIncPath, Dir_Destroy);
    Lst_Destroy(parseIncPath, Dir_Destroy);
    Lst_Destroy(includes, NULL);	/* Should be empty now */
#endif
}