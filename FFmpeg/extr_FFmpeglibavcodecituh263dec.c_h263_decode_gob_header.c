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
struct TYPE_4__ {int mb_num; unsigned int mb_y; unsigned int gob_index; unsigned int mb_height; void* qscale; int /*<<< orphan*/  gb; scalar_t__ mb_x; int /*<<< orphan*/  avctx; scalar_t__ h263_slice_structured; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 scalar_t__ check_marker (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ff_h263_decode_mba (TYPE_1__*) ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 unsigned int show_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int h263_decode_gob_header(MpegEncContext *s)
{
    unsigned int val, gob_number;
    int left;

    /* Check for GOB Start Code */
    val = show_bits(&s->gb, 16);
    if(val)
        return -1;

        /* We have a GBSC probably with GSTUFF */
    skip_bits(&s->gb, 16); /* Drop the zeros */
    left= get_bits_left(&s->gb);
    left = FFMIN(left, 32);
    //MN: we must check the bits left or we might end in an infinite loop (or segfault)
    for(;left>13; left--){
        if(get_bits1(&s->gb)) break; /* Seek the '1' bit */
    }
    if(left<=13)
        return -1;

    if(s->h263_slice_structured){
        if(check_marker(s->avctx, &s->gb, "before MBA")==0)
            return -1;

        ff_h263_decode_mba(s);

        if(s->mb_num > 1583)
            if(check_marker(s->avctx, &s->gb, "after MBA")==0)
                return -1;

        s->qscale = get_bits(&s->gb, 5); /* SQUANT */
        if(check_marker(s->avctx, &s->gb, "after SQUANT")==0)
            return -1;
        skip_bits(&s->gb, 2); /* GFID */
    }else{
        gob_number = get_bits(&s->gb, 5); /* GN */
        s->mb_x= 0;
        s->mb_y= s->gob_index* gob_number;
        skip_bits(&s->gb, 2); /* GFID */
        s->qscale = get_bits(&s->gb, 5); /* GQUANT */
    }

    if(s->mb_y >= s->mb_height)
        return -1;

    if(s->qscale==0)
        return -1;

    return 0;
}