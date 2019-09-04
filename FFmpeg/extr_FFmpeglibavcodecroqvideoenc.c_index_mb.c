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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int INT_MAX ; 
 int squared_diff_macroblock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int index_mb(uint8_t cluster[], uint8_t cb[], int numCB,
                    int *outIndex, int dim)
{
    int i, lDiff = INT_MAX, pick=0;

    /* Diff against the others */
    for (i=0; i<numCB; i++) {
        int diff = squared_diff_macroblock(cluster, cb + i*dim*dim*3, dim);
        if (diff < lDiff) {
            lDiff = diff;
            pick = i;
        }
    }

    *outIndex = pick;
    return lDiff;
}