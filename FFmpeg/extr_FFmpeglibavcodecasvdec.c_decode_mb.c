#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* clear_blocks ) (int /*<<< orphan*/ *) ;} ;
struct TYPE_9__ {TYPE_2__* avctx; TYPE_1__ bdsp; } ;
struct TYPE_8__ {scalar_t__ codec_id; } ;
typedef  TYPE_3__ ASV1Context ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_ASV1 ; 
 int asv1_decode_block (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int asv2_decode_block (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int decode_mb(ASV1Context *a, int16_t block[6][64])
{
    int i, ret;

    a->bdsp.clear_blocks(block[0]);

    if (a->avctx->codec_id == AV_CODEC_ID_ASV1) {
        for (i = 0; i < 6; i++) {
            if ((ret = asv1_decode_block(a, block[i])) < 0)
                return ret;
        }
    } else {
        for (i = 0; i < 6; i++) {
            if ((ret = asv2_decode_block(a, block[i])) < 0)
                return ret;
        }
    }
    return 0;
}