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
struct TYPE_3__ {int num_syms; int* weights; int* cum_prob; int* idx2sym; } ;
typedef  TYPE_1__ Model ;

/* Variables and functions */

__attribute__((used)) static void model_reset(Model *m)
{
    int i;

    for (i = 0; i <= m->num_syms; i++) {
        m->weights[i]  = 1;
        m->cum_prob[i] = m->num_syms - i;
    }
    m->weights[0] = 0;
    for (i = 0; i < m->num_syms; i++)
        m->idx2sym[i + 1] = i;
}