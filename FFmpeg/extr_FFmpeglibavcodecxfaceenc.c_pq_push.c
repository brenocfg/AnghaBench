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
struct TYPE_3__ {int prob_ranges_idx; int /*<<< orphan*/ * prob_ranges; } ;
typedef  TYPE_1__ ProbRangesQueue ;
typedef  int /*<<< orphan*/  ProbRange ;

/* Variables and functions */
 int XFACE_PIXELS ; 

__attribute__((used)) static inline int pq_push(ProbRangesQueue *pq, const ProbRange *p)
{
    if (pq->prob_ranges_idx >= XFACE_PIXELS * 2 - 1)
        return -1;
    pq->prob_ranges[pq->prob_ranges_idx++] = *p;
    return 0;
}