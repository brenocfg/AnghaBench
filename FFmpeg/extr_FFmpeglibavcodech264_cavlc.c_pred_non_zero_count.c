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
struct TYPE_6__ {int /*<<< orphan*/  avctx; } ;
struct TYPE_5__ {int* non_zero_count_cache; } ;
typedef  TYPE_1__ H264SliceContext ;
typedef  TYPE_2__ H264Context ;

/* Variables and functions */
 int /*<<< orphan*/  ff_tlog (int /*<<< orphan*/ ,char*,int const,int const,int,int,int) ; 
 int* scan8 ; 

__attribute__((used)) static inline int pred_non_zero_count(const H264Context *h, H264SliceContext *sl, int n)
{
    const int index8= scan8[n];
    const int left = sl->non_zero_count_cache[index8 - 1];
    const int top  = sl->non_zero_count_cache[index8 - 8];
    int i= left + top;

    if(i<64) i= (i+1)>>1;

    ff_tlog(h->avctx, "pred_nnz L%X T%X n%d s%d P%X\n", left, top, n, scan8[n], i&31);

    return i&31;
}