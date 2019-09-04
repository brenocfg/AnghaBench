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
struct TYPE_3__ {int flag; char const* suffix; } ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_1__*) ; 
 TYPE_1__* cpus ; 

__attribute__((used)) static const char *cpu_suffix(int cpu)
{
    int i = FF_ARRAY_ELEMS(cpus);

    while (--i >= 0)
        if (cpu & cpus[i].flag)
            return cpus[i].suffix;

    return "c";
}