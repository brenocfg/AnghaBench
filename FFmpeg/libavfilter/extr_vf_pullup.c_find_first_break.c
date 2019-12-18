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
struct TYPE_3__ {int breaks; struct TYPE_3__* next; } ;
typedef  TYPE_1__ PullupField ;

/* Variables and functions */
 int BREAK_LEFT ; 
 int BREAK_RIGHT ; 

__attribute__((used)) static int find_first_break(PullupField *f, int max)
{
    int i;

    for (i = 0; i < max; i++) {
        if (f->breaks & BREAK_RIGHT || f->next->breaks & BREAK_LEFT)
            return i + 1;
        f = f->next;
    }

    return 0;
}