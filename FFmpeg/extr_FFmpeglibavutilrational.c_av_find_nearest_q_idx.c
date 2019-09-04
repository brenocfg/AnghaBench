#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ den; } ;
typedef  TYPE_1__ AVRational ;

/* Variables and functions */
 scalar_t__ av_nearer_q (TYPE_1__,TYPE_1__ const,TYPE_1__ const) ; 

int av_find_nearest_q_idx(AVRational q, const AVRational* q_list)
{
    int i, nearest_q_idx = 0;
    for (i = 0; q_list[i].den; i++)
        if (av_nearer_q(q, q_list[i], q_list[nearest_q_idx]) > 0)
            nearest_q_idx = i;

    return nearest_q_idx;
}