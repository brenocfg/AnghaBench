#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_14__ {int /*<<< orphan*/ * rd_scratchpad; } ;
struct TYPE_16__ {int linesize; int lambda2; int /*<<< orphan*/ ** dest; int /*<<< orphan*/  block; TYPE_2__* avctx; void* tex_pb; void* pb2; scalar_t__ data_partitioning; void* pb; TYPE_1__ sc; int /*<<< orphan*/ * blocks; } ;
struct TYPE_15__ {scalar_t__ mb_decision; } ;
typedef  void* PutBitContext ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */
 int FF_LAMBDA_SHIFT ; 
 scalar_t__ FF_MB_DECISION_RD ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  copy_context_after_encode (TYPE_3__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  copy_context_before_encode (TYPE_3__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  encode_mb (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  ff_mpv_reconstruct_mb (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 int put_bits_count (void**) ; 
 int sse_mb (TYPE_3__*) ; 

__attribute__((used)) static inline void encode_mb_hq(MpegEncContext *s, MpegEncContext *backup, MpegEncContext *best, int type,
                           PutBitContext pb[2], PutBitContext pb2[2], PutBitContext tex_pb[2],
                           int *dmin, int *next_block, int motion_x, int motion_y)
{
    int score;
    uint8_t *dest_backup[3];

    copy_context_before_encode(s, backup, type);

    s->block= s->blocks[*next_block];
    s->pb= pb[*next_block];
    if(s->data_partitioning){
        s->pb2   = pb2   [*next_block];
        s->tex_pb= tex_pb[*next_block];
    }

    if(*next_block){
        memcpy(dest_backup, s->dest, sizeof(s->dest));
        s->dest[0] = s->sc.rd_scratchpad;
        s->dest[1] = s->sc.rd_scratchpad + 16*s->linesize;
        s->dest[2] = s->sc.rd_scratchpad + 16*s->linesize + 8;
        av_assert0(s->linesize >= 32); //FIXME
    }

    encode_mb(s, motion_x, motion_y);

    score= put_bits_count(&s->pb);
    if(s->data_partitioning){
        score+= put_bits_count(&s->pb2);
        score+= put_bits_count(&s->tex_pb);
    }

    if(s->avctx->mb_decision == FF_MB_DECISION_RD){
        ff_mpv_reconstruct_mb(s, s->block);

        score *= s->lambda2;
        score += sse_mb(s) << FF_LAMBDA_SHIFT;
    }

    if(*next_block){
        memcpy(s->dest, dest_backup, sizeof(s->dest));
    }

    if(score<*dmin){
        *dmin= score;
        *next_block^=1;

        copy_context_after_encode(best, s, type);
    }
}