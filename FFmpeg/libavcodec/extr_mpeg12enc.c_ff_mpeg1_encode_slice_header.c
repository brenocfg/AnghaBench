#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ codec_id; int height; int mb_y; int /*<<< orphan*/  pb; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_MPEG2VIDEO ; 
 scalar_t__ SLICE_MIN_START_CODE ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  put_header (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  put_qscale (TYPE_1__*) ; 

void ff_mpeg1_encode_slice_header(MpegEncContext *s)
{
    if (s->codec_id == AV_CODEC_ID_MPEG2VIDEO && s->height > 2800) {
        put_header(s, SLICE_MIN_START_CODE + (s->mb_y & 127));
        /* slice_vertical_position_extension */
        put_bits(&s->pb, 3, s->mb_y >> 7);
    } else {
        put_header(s, SLICE_MIN_START_CODE + s->mb_y);
    }
    put_qscale(s);
    /* slice extra information */
    put_bits(&s->pb, 1, 0);
}