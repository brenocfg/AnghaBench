#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  buf; } ;
struct TYPE_8__ {int* bs_code; int ch_mode; } ;
struct TYPE_9__ {int* sr_code; int channels; int bps_code; TYPE_3__ pb; int /*<<< orphan*/  frame_count; TYPE_1__ frame; } ;
typedef  TYPE_1__ FlacFrame ;
typedef  TYPE_2__ FlacEncodeContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CRC_8_ATM ; 
 int FLAC_CHMODE_INDEPENDENT ; 
 int FLAC_MAX_CHANNELS ; 
 int av_crc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_crc_get_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_put_bits (TYPE_3__*) ; 
 int /*<<< orphan*/  put_bits (TYPE_3__*,int,int) ; 
 int put_bits_count (TYPE_3__*) ; 
 int /*<<< orphan*/  write_utf8 (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_frame_header(FlacEncodeContext *s)
{
    FlacFrame *frame;
    int crc;

    frame = &s->frame;

    put_bits(&s->pb, 16, 0xFFF8);
    put_bits(&s->pb, 4, frame->bs_code[0]);
    put_bits(&s->pb, 4, s->sr_code[0]);

    if (frame->ch_mode == FLAC_CHMODE_INDEPENDENT)
        put_bits(&s->pb, 4, s->channels-1);
    else
        put_bits(&s->pb, 4, frame->ch_mode + FLAC_MAX_CHANNELS - 1);

    put_bits(&s->pb, 3, s->bps_code);
    put_bits(&s->pb, 1, 0);
    write_utf8(&s->pb, s->frame_count);

    if (frame->bs_code[0] == 6)
        put_bits(&s->pb, 8, frame->bs_code[1]);
    else if (frame->bs_code[0] == 7)
        put_bits(&s->pb, 16, frame->bs_code[1]);

    if (s->sr_code[0] == 12)
        put_bits(&s->pb, 8, s->sr_code[1]);
    else if (s->sr_code[0] > 12)
        put_bits(&s->pb, 16, s->sr_code[1]);

    flush_put_bits(&s->pb);
    crc = av_crc(av_crc_get_table(AV_CRC_8_ATM), 0, s->pb.buf,
                 put_bits_count(&s->pb) >> 3);
    put_bits(&s->pb, 8, crc);
}