#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int* color; int ref; int mx; int my; int level; int type; } ;
struct TYPE_12__ {int b_width; int block_max_depth; int nb_planes; int ref_frames; int /*<<< orphan*/ * block_state; int /*<<< orphan*/  c; scalar_t__ keyframe; TYPE_2__ const* block; } ;
typedef  TYPE_1__ SnowContext ;
typedef  TYPE_2__ const BlockNode ;

/* Variables and functions */
 int BLOCK_INTRA ; 
 int FFABS (int) ; 
 int av_log2 (int) ; 
 TYPE_2__ const null_block ; 
 int /*<<< orphan*/  pred_mv (TYPE_1__*,int*,int*,int,TYPE_2__ const*,TYPE_2__ const*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  put_rac (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_symbol (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ same_block (TYPE_2__ const*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  set_blocks (TYPE_1__*,int,int,int,int,int,int,int,int,int,int) ; 

__attribute__((used)) static void encode_q_branch2(SnowContext *s, int level, int x, int y){
    const int w= s->b_width  << s->block_max_depth;
    const int rem_depth= s->block_max_depth - level;
    const int index= (x + y*w) << rem_depth;
    int trx= (x+1)<<rem_depth;
    BlockNode *b= &s->block[index];
    const BlockNode *left  = x ? &s->block[index-1] : &null_block;
    const BlockNode *top   = y ? &s->block[index-w] : &null_block;
    const BlockNode *tl    = y && x ? &s->block[index-w-1] : left;
    const BlockNode *tr    = y && trx<w && ((x&1)==0 || level==0) ? &s->block[index-w+(1<<rem_depth)] : tl; //FIXME use lt
    int pl = left->color[0];
    int pcb= left->color[1];
    int pcr= left->color[2];
    int pmx, pmy;
    int ref_context= av_log2(2*left->ref) + av_log2(2*top->ref);
    int mx_context= av_log2(2*FFABS(left->mx - top->mx)) + 16*!!b->ref;
    int my_context= av_log2(2*FFABS(left->my - top->my)) + 16*!!b->ref;
    int s_context= 2*left->level + 2*top->level + tl->level + tr->level;

    if(s->keyframe){
        set_blocks(s, level, x, y, pl, pcb, pcr, 0, 0, 0, BLOCK_INTRA);
        return;
    }

    if(level!=s->block_max_depth){
        if(same_block(b,b+1) && same_block(b,b+w) && same_block(b,b+w+1)){
            put_rac(&s->c, &s->block_state[4 + s_context], 1);
        }else{
            put_rac(&s->c, &s->block_state[4 + s_context], 0);
            encode_q_branch2(s, level+1, 2*x+0, 2*y+0);
            encode_q_branch2(s, level+1, 2*x+1, 2*y+0);
            encode_q_branch2(s, level+1, 2*x+0, 2*y+1);
            encode_q_branch2(s, level+1, 2*x+1, 2*y+1);
            return;
        }
    }
    if(b->type & BLOCK_INTRA){
        pred_mv(s, &pmx, &pmy, 0, left, top, tr);
        put_rac(&s->c, &s->block_state[1 + (left->type&1) + (top->type&1)], 1);
        put_symbol(&s->c, &s->block_state[32], b->color[0]-pl , 1);
        if (s->nb_planes > 2) {
            put_symbol(&s->c, &s->block_state[64], b->color[1]-pcb, 1);
            put_symbol(&s->c, &s->block_state[96], b->color[2]-pcr, 1);
        }
        set_blocks(s, level, x, y, b->color[0], b->color[1], b->color[2], pmx, pmy, 0, BLOCK_INTRA);
    }else{
        pred_mv(s, &pmx, &pmy, b->ref, left, top, tr);
        put_rac(&s->c, &s->block_state[1 + (left->type&1) + (top->type&1)], 0);
        if(s->ref_frames > 1)
            put_symbol(&s->c, &s->block_state[128 + 1024 + 32*ref_context], b->ref, 0);
        put_symbol(&s->c, &s->block_state[128 + 32*mx_context], b->mx - pmx, 1);
        put_symbol(&s->c, &s->block_state[128 + 32*my_context], b->my - pmy, 1);
        set_blocks(s, level, x, y, pl, pcb, pcr, b->mx, b->my, b->ref, 0);
    }
}