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
typedef  int uint64_t ;
struct TYPE_3__ {int* utility_inc; int numCB; int /*<<< orphan*/ * cells; int /*<<< orphan*/  rand_state; } ;
typedef  TYPE_1__ elbg_data ;

/* Variables and functions */
 int INT_MAX ; 
 int /*<<< orphan*/  av_assert2 (int /*<<< orphan*/ ) ; 
 int av_lfg_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_high_utility_cell(elbg_data *elbg)
{
    int i=0;
    /* Using linear search, do binary if it ever turns to be speed critical */
    uint64_t r;

    if (elbg->utility_inc[elbg->numCB-1] < INT_MAX) {
        r = av_lfg_get(elbg->rand_state) % (unsigned int)elbg->utility_inc[elbg->numCB-1] + 1;
    } else {
        r = av_lfg_get(elbg->rand_state);
        r = (av_lfg_get(elbg->rand_state) + (r<<32)) % elbg->utility_inc[elbg->numCB-1] + 1;
    }

    while (elbg->utility_inc[i] < r) {
        i++;
    }

    av_assert2(elbg->cells[i]);

    return i;
}