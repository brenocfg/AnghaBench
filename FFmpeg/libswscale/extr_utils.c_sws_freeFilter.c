#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  chrV; int /*<<< orphan*/  chrH; int /*<<< orphan*/  lumV; int /*<<< orphan*/  lumH; } ;
typedef  TYPE_1__ SwsFilter ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (TYPE_1__*) ; 
 int /*<<< orphan*/  sws_freeVec (int /*<<< orphan*/ ) ; 

void sws_freeFilter(SwsFilter *filter)
{
    if (!filter)
        return;

    sws_freeVec(filter->lumH);
    sws_freeVec(filter->lumV);
    sws_freeVec(filter->chrH);
    sws_freeVec(filter->chrV);
    av_free(filter);
}