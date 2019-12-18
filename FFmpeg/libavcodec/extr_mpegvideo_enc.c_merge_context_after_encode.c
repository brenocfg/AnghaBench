#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * encoding_error; } ;
struct TYPE_11__ {int /*<<< orphan*/  error_count; } ;
struct TYPE_10__ {int /*<<< orphan*/  buf; } ;
struct TYPE_9__ {TYPE_2__ pb; scalar_t__ noise_reduction; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  MERGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_assert1 (int) ; 
 int /*<<< orphan*/  avpriv_copy_bits (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b_count ; 
 TYPE_7__ current_picture ; 
 int /*<<< orphan*/ * dct_count ; 
 int /*<<< orphan*/ ** dct_error_sum ; 
 TYPE_6__ er ; 
 int /*<<< orphan*/  f_count ; 
 int /*<<< orphan*/  flush_put_bits (TYPE_2__*) ; 
 int /*<<< orphan*/  i_count ; 
 int /*<<< orphan*/  i_tex_bits ; 
 int /*<<< orphan*/  misc_bits ; 
 int /*<<< orphan*/  mv_bits ; 
 int /*<<< orphan*/  p_tex_bits ; 
 int /*<<< orphan*/  padding_bug_score ; 
 int put_bits_count (TYPE_2__*) ; 
 int /*<<< orphan*/  skip_count ; 

__attribute__((used)) static void merge_context_after_encode(MpegEncContext *dst, MpegEncContext *src){
    int i;

    MERGE(dct_count[0]); //note, the other dct vars are not part of the context
    MERGE(dct_count[1]);
    MERGE(mv_bits);
    MERGE(i_tex_bits);
    MERGE(p_tex_bits);
    MERGE(i_count);
    MERGE(f_count);
    MERGE(b_count);
    MERGE(skip_count);
    MERGE(misc_bits);
    MERGE(er.error_count);
    MERGE(padding_bug_score);
    MERGE(current_picture.encoding_error[0]);
    MERGE(current_picture.encoding_error[1]);
    MERGE(current_picture.encoding_error[2]);

    if (dst->noise_reduction){
        for(i=0; i<64; i++){
            MERGE(dct_error_sum[0][i]);
            MERGE(dct_error_sum[1][i]);
        }
    }

    av_assert1(put_bits_count(&src->pb) % 8 ==0);
    av_assert1(put_bits_count(&dst->pb) % 8 ==0);
    avpriv_copy_bits(&dst->pb, src->pb.buf, put_bits_count(&src->pb));
    flush_put_bits(&dst->pb);
}