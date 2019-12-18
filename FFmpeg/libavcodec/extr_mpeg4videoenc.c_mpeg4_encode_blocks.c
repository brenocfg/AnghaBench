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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_8__ {int /*<<< orphan*/ * permutated; } ;
struct TYPE_9__ {TYPE_2__ intra_scantable; int /*<<< orphan*/  pb; TYPE_1__* avctx; } ;
struct TYPE_7__ {int flags2; } ;
typedef  int /*<<< orphan*/  PutBitContext ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */
 int AV_CODEC_FLAG2_NO_OUTPUT ; 
 int /*<<< orphan*/  mpeg4_encode_block (TYPE_3__*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpeg4_get_block_length (TYPE_3__*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_put_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mpeg4_encode_blocks(MpegEncContext *s, int16_t block[6][64],
                                       int intra_dc[6], uint8_t **scan_table,
                                       PutBitContext *dc_pb,
                                       PutBitContext *ac_pb)
{
    int i;

    if (scan_table) {
        if (s->avctx->flags2 & AV_CODEC_FLAG2_NO_OUTPUT) {
            for (i = 0; i < 6; i++)
                skip_put_bits(&s->pb,
                              mpeg4_get_block_length(s, block[i], i,
                                                     intra_dc[i], scan_table[i]));
        } else {
            /* encode each block */
            for (i = 0; i < 6; i++)
                mpeg4_encode_block(s, block[i], i,
                                   intra_dc[i], scan_table[i], dc_pb, ac_pb);
        }
    } else {
        if (s->avctx->flags2 & AV_CODEC_FLAG2_NO_OUTPUT) {
            for (i = 0; i < 6; i++)
                skip_put_bits(&s->pb,
                              mpeg4_get_block_length(s, block[i], i, 0,
                                                     s->intra_scantable.permutated));
        } else {
            /* encode each block */
            for (i = 0; i < 6; i++)
                mpeg4_encode_block(s, block[i], i, 0,
                                   s->intra_scantable.permutated, dc_pb, ac_pb);
        }
    }
}