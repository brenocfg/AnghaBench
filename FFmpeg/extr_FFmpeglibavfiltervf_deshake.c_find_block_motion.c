#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {scalar_t__ search; int ry; int rx; int (* sad ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ;} ;
struct TYPE_5__ {int x; int y; } ;
typedef  TYPE_1__ IntMotionVector ;
typedef  TYPE_2__ DeshakeContext ;

/* Variables and functions */
 scalar_t__ EXHAUSTIVE ; 
 int INT_MAX ; 
 scalar_t__ SMART_EXHAUSTIVE ; 
 int /*<<< orphan*/  emms_c () ; 
 int stub1 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int stub2 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int stub3 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void find_block_motion(DeshakeContext *deshake, uint8_t *src1,
                              uint8_t *src2, int cx, int cy, int stride,
                              IntMotionVector *mv)
{
    int x, y;
    int diff;
    int smallest = INT_MAX;
    int tmp, tmp2;

    #define CMP(i, j) deshake->sad(src1 + cy  * stride + cx,  stride,\
                                   src2 + (j) * stride + (i), stride)

    if (deshake->search == EXHAUSTIVE) {
        // Compare every possible position - this is sloooow!
        for (y = -deshake->ry; y <= deshake->ry; y++) {
            for (x = -deshake->rx; x <= deshake->rx; x++) {
                diff = CMP(cx - x, cy - y);
                if (diff < smallest) {
                    smallest = diff;
                    mv->x = x;
                    mv->y = y;
                }
            }
        }
    } else if (deshake->search == SMART_EXHAUSTIVE) {
        // Compare every other possible position and find the best match
        for (y = -deshake->ry + 1; y < deshake->ry; y += 2) {
            for (x = -deshake->rx + 1; x < deshake->rx; x += 2) {
                diff = CMP(cx - x, cy - y);
                if (diff < smallest) {
                    smallest = diff;
                    mv->x = x;
                    mv->y = y;
                }
            }
        }

        // Hone in on the specific best match around the match we found above
        tmp = mv->x;
        tmp2 = mv->y;

        for (y = tmp2 - 1; y <= tmp2 + 1; y++) {
            for (x = tmp - 1; x <= tmp + 1; x++) {
                if (x == tmp && y == tmp2)
                    continue;

                diff = CMP(cx - x, cy - y);
                if (diff < smallest) {
                    smallest = diff;
                    mv->x = x;
                    mv->y = y;
                }
            }
        }
    }

    if (smallest > 512) {
        mv->x = -1;
        mv->y = -1;
    }
    emms_c();
    //av_log(NULL, AV_LOG_ERROR, "%d\n", smallest);
    //av_log(NULL, AV_LOG_ERROR, "Final: (%d, %d) = %d x %d\n", cx, cy, mv->x, mv->y);
}