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
struct TYPE_6__ {int bypp; int lrange; int urange; TYPE_1__* avctx; } ;
typedef  TYPE_2__ ZmbvEncContext ;
struct TYPE_5__ {scalar_t__ height; scalar_t__ width; } ;

/* Variables and functions */
 int FFMIN (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ZMBV_BLOCK ; 
 int block_cmp (TYPE_2__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int,int,int*) ; 

__attribute__((used)) static int zmbv_me(ZmbvEncContext *c, uint8_t *src, int sstride, uint8_t *prev,
                   int pstride, int x, int y, int *mx, int *my, int *xored)
{
    int dx, dy, txored, tv, bv, bw, bh;
    int mx0, my0;

    mx0 = *mx;
    my0 = *my;
    bw = FFMIN(ZMBV_BLOCK, c->avctx->width - x);
    bh = FFMIN(ZMBV_BLOCK, c->avctx->height - y);

    /* Try (0,0) */
    bv = block_cmp(c, src, sstride, prev, pstride, bw, bh, xored);
    *mx = *my = 0;
    if(!bv) return 0;

    /* Try previous block's MV (if not 0,0) */
    if (mx0 || my0){
        tv = block_cmp(c, src, sstride, prev + mx0 * c->bypp + my0 * pstride, pstride, bw, bh, &txored);
        if(tv < bv){
            bv = tv;
            *mx = mx0;
            *my = my0;
            *xored = txored;
            if(!bv) return 0;
        }
    }

    /* Try other MVs from top-to-bottom, left-to-right */
    for(dy = -c->lrange; dy <= c->urange; dy++){
        for(dx = -c->lrange; dx <= c->urange; dx++){
            if(!dx && !dy) continue; // we already tested this block
            if(dx == mx0 && dy == my0) continue; // this one too
            tv = block_cmp(c, src, sstride, prev + dx * c->bypp + dy * pstride, pstride, bw, bh, &txored);
            if(tv < bv){
                 bv = tv;
                 *mx = dx;
                 *my = dy;
                 *xored = txored;
                 if(!bv) return 0;
             }
         }
    }
    return bv;
}