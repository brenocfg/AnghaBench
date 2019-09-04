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
typedef  int uint8_t ;
struct TYPE_3__ {int tpitchuv; int tpitchy; int* tbuffer; } ;
typedef  TYPE_1__ FieldMatchContext ;

/* Variables and functions */
 int FFMAX (int,int /*<<< orphan*/ ) ; 
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  build_abs_diff_mask (int const*,int,int const*,int,int*,int,int,int) ; 

__attribute__((used)) static void build_diff_map(FieldMatchContext *fm,
                           const uint8_t *prvp, int prv_linesize,
                           const uint8_t *nxtp, int nxt_linesize,
                           uint8_t *dstp, int dst_linesize, int height,
                           int width, int plane)
{
    int x, y, u, diff, count;
    int tpitch = plane ? fm->tpitchuv : fm->tpitchy;
    const uint8_t *dp = fm->tbuffer + tpitch;

    build_abs_diff_mask(prvp, prv_linesize, nxtp, nxt_linesize,
                        fm->tbuffer, tpitch, width, height>>1);

    for (y = 2; y < height - 2; y += 2) {
        for (x = 1; x < width - 1; x++) {
            diff = dp[x];
            if (diff > 3) {
                for (count = 0, u = x-1; u < x+2 && count < 2; u++) {
                    count += dp[u-tpitch] > 3;
                    count += dp[u       ] > 3;
                    count += dp[u+tpitch] > 3;
                }
                if (count > 1) {
                    dstp[x] = 1;
                    if (diff > 19) {
                        int upper = 0, lower = 0;
                        for (count = 0, u = x-1; u < x+2 && count < 6; u++) {
                            if (dp[u-tpitch] > 19) { count++; upper = 1; }
                            if (dp[u       ] > 19)   count++;
                            if (dp[u+tpitch] > 19) { count++; lower = 1; }
                        }
                        if (count > 3) {
                            if (upper && lower) {
                                dstp[x] |= 1<<1;
                            } else {
                                int upper2 = 0, lower2 = 0;
                                for (u = FFMAX(x-4,0); u < FFMIN(x+5,width); u++) {
                                    if (y != 2 &&        dp[u-2*tpitch] > 19) upper2 = 1;
                                    if (                 dp[u-  tpitch] > 19) upper  = 1;
                                    if (                 dp[u+  tpitch] > 19) lower  = 1;
                                    if (y != height-4 && dp[u+2*tpitch] > 19) lower2 = 1;
                                }
                                if ((upper && (lower || upper2)) ||
                                    (lower && (upper || lower2)))
                                    dstp[x] |= 1<<1;
                                else if (count > 5)
                                    dstp[x] |= 1<<2;
                            }
                        }
                    }
                }
            }
        }
        dp += tpitch;
        dstp += dst_linesize;
    }
}