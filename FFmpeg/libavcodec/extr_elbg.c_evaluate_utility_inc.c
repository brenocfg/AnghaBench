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
typedef  int int64_t ;
struct TYPE_3__ {int numCB; int* utility; int error; int* utility_inc; } ;
typedef  TYPE_1__ elbg_data ;

/* Variables and functions */

__attribute__((used)) static void evaluate_utility_inc(elbg_data *elbg)
{
    int i;
    int64_t inc=0;

    for (i=0; i < elbg->numCB; i++) {
        if (elbg->numCB*elbg->utility[i] > elbg->error)
            inc += elbg->utility[i];
        elbg->utility_inc[i] = inc;
    }
}