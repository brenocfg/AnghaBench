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
struct TYPE_3__ {int* weights; size_t num_syms; int* cum_prob; } ;
typedef  TYPE_1__ Model ;

/* Variables and functions */
 int FFMIN (int,int) ; 

__attribute__((used)) static int model_calc_threshold(Model *m)
{
    int thr;

    thr = 2 * m->weights[m->num_syms] - 1;
    thr = ((thr >> 1) + 4 * m->cum_prob[0]) / thr;

    return FFMIN(thr, 0x3FFF);
}