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
struct TYPE_4__ {int mb_num; int qscale; scalar_t__ pict_type; int gob_index; int /*<<< orphan*/  pb; scalar_t__ h263_slice_structured; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
 scalar_t__ AV_PICTURE_TYPE_I ; 
 int /*<<< orphan*/  ff_h263_encode_mba (TYPE_1__*) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 

void ff_h263_encode_gob_header(MpegEncContext * s, int mb_line)
{
    put_bits(&s->pb, 17, 1); /* GBSC */

    if(s->h263_slice_structured){
        put_bits(&s->pb, 1, 1);

        ff_h263_encode_mba(s);

        if(s->mb_num > 1583)
            put_bits(&s->pb, 1, 1);
        put_bits(&s->pb, 5, s->qscale); /* GQUANT */
        put_bits(&s->pb, 1, 1);
        put_bits(&s->pb, 2, s->pict_type == AV_PICTURE_TYPE_I); /* GFID */
    }else{
        int gob_number= mb_line / s->gob_index;

        put_bits(&s->pb, 5, gob_number); /* GN */
        put_bits(&s->pb, 2, s->pict_type == AV_PICTURE_TYPE_I); /* GFID */
        put_bits(&s->pb, 5, s->qscale); /* GQUANT */
    }
}