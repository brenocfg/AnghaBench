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
typedef  int /*<<< orphan*/  ProbRangesQueue ;
typedef  int /*<<< orphan*/  ProbRange ;

/* Variables and functions */
 int XFACE_WIDTH ; 
 int /*<<< orphan*/ * ff_xface_probranges_2x2 ; 
 int /*<<< orphan*/  pq_push (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void push_greys(ProbRangesQueue *pq, char *bitmap, int w, int h)
{
    if (w > 3) {
        w /= 2;
        h /= 2;
        push_greys(pq, bitmap,                       w, h);
        push_greys(pq, bitmap + w,                   w, h);
        push_greys(pq, bitmap + XFACE_WIDTH * h,     w, h);
        push_greys(pq, bitmap + XFACE_WIDTH * h + w, w, h);
    } else {
        const ProbRange *p = ff_xface_probranges_2x2 +
                 *bitmap +
            2 * *(bitmap + 1) +
            4 * *(bitmap + XFACE_WIDTH) +
            8 * *(bitmap + XFACE_WIDTH + 1);
        pq_push(pq, p);
    }
}