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
struct arg_hdr {int flag; } ;

/* Variables and functions */
 int ARG_TERMINATOR ; 

__attribute__((used)) static
int arg_endindex(struct arg_hdr * *table)
{
    int tabindex = 0;
    while (!(table[tabindex]->flag & ARG_TERMINATOR))
        tabindex++;
    return tabindex;
}