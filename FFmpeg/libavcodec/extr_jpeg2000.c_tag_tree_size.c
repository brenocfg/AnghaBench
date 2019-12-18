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
typedef  int int64_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int INT32_MAX ; 
 int /*<<< orphan*/  av_assert0 (int) ; 

__attribute__((used)) static int32_t tag_tree_size(int w, int h)
{
    int64_t res = 0;
    while (w > 1 || h > 1) {
        res += w * (int64_t)h;
        av_assert0(res + 1 < INT32_MAX);
        w = (w + 1) >> 1;
        h = (h + 1) >> 1;
    }
    return (int32_t)(res + 1);
}