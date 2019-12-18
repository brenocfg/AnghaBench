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
struct TYPE_4__ {int poc; } ;
typedef  TYPE_1__ H264Picture ;

/* Variables and functions */
 int INT_MAX ; 
 int INT_MIN ; 

__attribute__((used)) static int add_sorted(H264Picture **sorted, H264Picture * const *src,
                      int len, int limit, int dir)
{
    int i, best_poc;
    int out_i = 0;

    for (;;) {
        best_poc = dir ? INT_MIN : INT_MAX;

        for (i = 0; i < len; i++) {
            const int poc = src[i]->poc;
            if (((poc > limit) ^ dir) && ((poc < best_poc) ^ dir)) {
                best_poc      = poc;
                sorted[out_i] = src[i];
            }
        }
        if (best_poc == (dir ? INT_MIN : INT_MAX))
            break;
        limit = sorted[out_i++]->poc - dir;
    }
    return out_i;
}