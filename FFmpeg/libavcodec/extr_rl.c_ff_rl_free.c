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
struct TYPE_3__ {int /*<<< orphan*/ * index_run; int /*<<< orphan*/ * max_level; int /*<<< orphan*/ * max_run; } ;
typedef  TYPE_1__ RLTable ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 

void ff_rl_free(RLTable *rl)
{
    int i;

    for (i = 0; i < 2; i++) {
        av_freep(&rl->max_run[i]);
        av_freep(&rl->max_level[i]);
        av_freep(&rl->index_run[i]);
    }
}