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
 void* Targ_NewGN (char*) ; 
 void* VAR_CMD ; 
 void* VAR_GLOBAL ; 
 void* VAR_INTERNAL ; 

void
Var_Init(void)
{
    VAR_INTERNAL = Targ_NewGN("Internal");
    VAR_GLOBAL = Targ_NewGN("Global");
    VAR_CMD = Targ_NewGN("Command");

}