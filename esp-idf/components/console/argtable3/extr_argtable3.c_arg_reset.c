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
struct arg_hdr {int flag; int /*<<< orphan*/  parent; int /*<<< orphan*/  (* resetfn ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ARG_TERMINATOR ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void arg_reset(void * *argtable)
{
    struct arg_hdr * *table = (struct arg_hdr * *)argtable;
    int tabindex = 0;
    /*printf("arg_reset(%p)\n",argtable);*/
    do
    {
        if (table[tabindex]->resetfn)
            table[tabindex]->resetfn(table[tabindex]->parent);
    } while(!(table[tabindex++]->flag & ARG_TERMINATOR));
}