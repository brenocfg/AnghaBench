#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int level; int* color; int mx; int my; unsigned int ref; int type; } ;
struct TYPE_10__ {int b_width; int block_max_depth; int nb_planes; int ref_frames; int /*<<< orphan*/ * block_state; int /*<<< orphan*/  c; int /*<<< orphan*/  avctx; scalar_t__ keyframe; TYPE_2__ const* block; } ;
typedef  TYPE_1__ SnowContext ;
typedef  TYPE_2__ const BlockNode ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int BLOCK_INTRA ; 
 int FFABS (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int av_log2 (int) ; 
 scalar_t__ get_rac (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* get_symbol (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_2__ const null_block ; 
 int /*<<< orphan*/  pred_mv (TYPE_1__*,int*,int*,unsigned int,TYPE_2__ const*,TYPE_2__ const*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  set_blocks (TYPE_1__*,int,int,int,int,int,int,int,int,unsigned int,int) ; 

__attribute__((used)) static int decode_q_branch(SnowContext *s, int level, int x, int y){
    const int w= s->b_width << s->block_max_depth;
    const int rem_depth= s->block_max_depth - level;
    const int index= (x + y*w) << rem_depth;
    int trx= (x+1)<<rem_depth;
    const BlockNode *left  = x ? &s->block[index-1] : &null_block;
    const BlockNode *top   = y ? &s->block[index-w] : &null_block;
    const BlockNode *tl    = y && x ? &s->block[index-w-1] : left;
    const BlockNode *tr    = y && trx<w && ((x&1)==0 || level==0) ? &s->block[index-w+(1<<rem_depth)] : tl; //FIXME use lt
    int s_context= 2*left->level + 2*top->level + tl->level + tr->level;
    int res;

    if(s->keyframe){
        set_blocks(s, level, x, y, null_block.color[0], null_block.color[1], null_block.color[2], null_block.mx, null_block.my, null_block.ref, BLOCK_INTRA);
        return 0;
    }

    if(level==s->block_max_depth || get_rac(&s->c, &s->block_state[4 + s_context])){
        int type, mx, my;
        int l = left->color[0];
        int cb= left->color[1];
        int cr= left->color[2];
        unsigned ref = 0;
        int ref_context= av_log2(2*left->ref) + av_log2(2*top->ref);
        int mx_context= av_log2(2*FFABS(left->mx - top->mx)) + 0*av_log2(2*FFABS(tr->mx - top->mx));
        int my_context= av_log2(2*FFABS(left->my - top->my)) + 0*av_log2(2*FFABS(tr->my - top->my));

        type= get_rac(&s->c, &s->block_state[1 + left->type + top->type]) ? BLOCK_INTRA : 0;
        if(type){
            int ld, cbd, crd;
            pred_mv(s, &mx, &my, 0, left, top, tr);
            ld = get_symbol(&s->c, &s->block_state[32], 1);
            if (ld < -255 || ld > 255) {
                return AVERROR_INVALIDDATA;
            }
            l += ld;
            if (s->nb_planes > 2) {
                cbd = get_symbol(&s->c, &s->block_state[64], 1);
                crd = get_symbol(&s->c, &s->block_state[96], 1);
                if (cbd < -255 || cbd > 255 || crd < -255 || crd > 255) {
                    return AVERROR_INVALIDDATA;
                }
                cb += cbd;
                cr += crd;
            }
        }else{
            if(s->ref_frames > 1)
                ref= get_symbol(&s->c, &s->block_state[128 + 1024 + 32*ref_context], 0);
            if (ref >= s->ref_frames) {
                av_log(s->avctx, AV_LOG_ERROR, "Invalid ref\n");
                return AVERROR_INVALIDDATA;
            }
            pred_mv(s, &mx, &my, ref, left, top, tr);
            mx+= (unsigned)get_symbol(&s->c, &s->block_state[128 + 32*(mx_context + 16*!!ref)], 1);
            my+= (unsigned)get_symbol(&s->c, &s->block_state[128 + 32*(my_context + 16*!!ref)], 1);
        }
        set_blocks(s, level, x, y, l, cb, cr, mx, my, ref, type);
    }else{
        if ((res = decode_q_branch(s, level+1, 2*x+0, 2*y+0)) < 0 ||
            (res = decode_q_branch(s, level+1, 2*x+1, 2*y+0)) < 0 ||
            (res = decode_q_branch(s, level+1, 2*x+0, 2*y+1)) < 0 ||
            (res = decode_q_branch(s, level+1, 2*x+1, 2*y+1)) < 0)
            return res;
    }
    return 0;
}