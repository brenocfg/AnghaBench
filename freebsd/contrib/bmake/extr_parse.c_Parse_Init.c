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

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 void* Lst_Init (int /*<<< orphan*/ ) ; 
 void* defIncPath ; 
 void* includes ; 
 int /*<<< orphan*/ * mainNode ; 
 void* parseIncPath ; 
 void* sysIncPath ; 
 void* targCmds ; 

void
Parse_Init(void)
{
    mainNode = NULL;
    parseIncPath = Lst_Init(FALSE);
    sysIncPath = Lst_Init(FALSE);
    defIncPath = Lst_Init(FALSE);
    includes = Lst_Init(FALSE);
#ifdef CLEANUP
    targCmds = Lst_Init(FALSE);
#endif
}