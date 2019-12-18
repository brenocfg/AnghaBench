#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  esc3_level_length; int /*<<< orphan*/  qscale; int /*<<< orphan*/  interlaced_dct; int /*<<< orphan*/ * block_last_index; int /*<<< orphan*/  block; int /*<<< orphan*/  tex_pb; int /*<<< orphan*/  pb2; scalar_t__ data_partitioning; int /*<<< orphan*/  pb; int /*<<< orphan*/  mv_dir; int /*<<< orphan*/  mv_type; int /*<<< orphan*/  mb_skipped; int /*<<< orphan*/  mb_intra; int /*<<< orphan*/  misc_bits; int /*<<< orphan*/  skip_count; int /*<<< orphan*/  b_count; int /*<<< orphan*/  f_count; int /*<<< orphan*/  i_count; int /*<<< orphan*/  p_tex_bits; int /*<<< orphan*/  i_tex_bits; int /*<<< orphan*/  mv_bits; int /*<<< orphan*/ * last_dc; int /*<<< orphan*/  mb_skip_run; int /*<<< orphan*/  last_mv; int /*<<< orphan*/  mv; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void copy_context_after_encode(MpegEncContext *d, MpegEncContext *s, int type){
    int i;

    memcpy(d->mv, s->mv, 2*4*2*sizeof(int));
    memcpy(d->last_mv, s->last_mv, 2*2*2*sizeof(int)); //FIXME is memcpy faster than a loop?

    /* MPEG-1 */
    d->mb_skip_run= s->mb_skip_run;
    for(i=0; i<3; i++)
        d->last_dc[i] = s->last_dc[i];

    /* statistics */
    d->mv_bits= s->mv_bits;
    d->i_tex_bits= s->i_tex_bits;
    d->p_tex_bits= s->p_tex_bits;
    d->i_count= s->i_count;
    d->f_count= s->f_count;
    d->b_count= s->b_count;
    d->skip_count= s->skip_count;
    d->misc_bits= s->misc_bits;

    d->mb_intra= s->mb_intra;
    d->mb_skipped= s->mb_skipped;
    d->mv_type= s->mv_type;
    d->mv_dir= s->mv_dir;
    d->pb= s->pb;
    if(s->data_partitioning){
        d->pb2= s->pb2;
        d->tex_pb= s->tex_pb;
    }
    d->block= s->block;
    for(i=0; i<8; i++)
        d->block_last_index[i]= s->block_last_index[i];
    d->interlaced_dct= s->interlaced_dct;
    d->qscale= s->qscale;

    d->esc3_level_length= s->esc3_level_length;
}