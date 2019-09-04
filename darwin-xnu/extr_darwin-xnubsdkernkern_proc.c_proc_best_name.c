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
typedef  TYPE_1__* proc_t ;
struct TYPE_3__ {scalar_t__* p_name; char* p_comm; } ;

/* Variables and functions */

char *
proc_best_name(proc_t p)
{
    if (p->p_name[0] != 0)
        return (&p->p_name[0]);
    return (&p->p_comm[0]);
}