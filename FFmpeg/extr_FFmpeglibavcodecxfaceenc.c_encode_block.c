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

/* Variables and functions */
 size_t XFACE_COLOR_BLACK ; 
 size_t XFACE_COLOR_GREY ; 
 size_t XFACE_COLOR_WHITE ; 
 int XFACE_WIDTH ; 
 scalar_t__ all_black (char*,int,int) ; 
 scalar_t__ all_white (char*,int,int) ; 
 int /*<<< orphan*/ ** ff_xface_probranges_per_level ; 
 int /*<<< orphan*/  pq_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  push_greys (int /*<<< orphan*/ *,char*,int,int) ; 

__attribute__((used)) static void encode_block(char *bitmap, int w, int h, int level, ProbRangesQueue *pq)
{
    if (all_white(bitmap, w, h)) {
        pq_push(pq, &ff_xface_probranges_per_level[level][XFACE_COLOR_WHITE]);
    } else if (all_black(bitmap, w, h)) {
        pq_push(pq, &ff_xface_probranges_per_level[level][XFACE_COLOR_BLACK]);
        push_greys(pq, bitmap, w, h);
    } else {
        pq_push(pq, &ff_xface_probranges_per_level[level][XFACE_COLOR_GREY]);
        w /= 2;
        h /= 2;
        level++;
        encode_block(bitmap,                       w, h, level, pq);
        encode_block(bitmap + w,                   w, h, level, pq);
        encode_block(bitmap + h * XFACE_WIDTH,     w, h, level, pq);
        encode_block(bitmap + w + h * XFACE_WIDTH, w, h, level, pq);
    }
}