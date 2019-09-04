#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_5__ {int /*<<< orphan*/  permutated; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* clear_blocks ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  mb_y; int /*<<< orphan*/  mb_x; int /*<<< orphan*/  avctx; int /*<<< orphan*/  last_dc; TYPE_1__ intra_scantable; int /*<<< orphan*/  intra_matrix; int /*<<< orphan*/  gb; TYPE_2__ bdsp; } ;
typedef  TYPE_3__ TqiContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ff_mpeg1_decode_block_intra (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tqi_decode_mb(TqiContext *t, int16_t (*block)[64])
{
    int n;

    t->bdsp.clear_blocks(block[0]);
    for (n = 0; n < 6; n++) {
        int ret = ff_mpeg1_decode_block_intra(&t->gb,
                                              t->intra_matrix,
                                              t->intra_scantable.permutated,
                                              t->last_dc, block[n], n, 1);
        if (ret < 0) {
            av_log(t->avctx, AV_LOG_ERROR, "ac-tex damaged at %d %d\n",
                   t->mb_x, t->mb_y);
            return ret;
        }
    }

    return 0;
}