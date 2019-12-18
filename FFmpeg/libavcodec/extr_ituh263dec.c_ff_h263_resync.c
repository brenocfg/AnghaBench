#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ codec_id; int /*<<< orphan*/  gb; TYPE_1__* avctx; int /*<<< orphan*/  last_resync_gb; scalar_t__ studio_profile; } ;
struct TYPE_5__ {int /*<<< orphan*/  priv_data; } ;
typedef  TYPE_2__ MpegEncContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_MPEG4 ; 
 scalar_t__ CONFIG_MPEG4_DECODER ; 
 scalar_t__ SLICE_START_CODE ; 
 int /*<<< orphan*/  align_get_bits (int /*<<< orphan*/ *) ; 
 int ff_mpeg4_decode_video_packet_header (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int h263_decode_gob_header (TYPE_2__*) ; 
 scalar_t__ show_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ show_bits_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits1 (int /*<<< orphan*/ *) ; 

int ff_h263_resync(MpegEncContext *s){
    int left, pos, ret;

    /* In MPEG-4 studio mode look for a new slice startcode
     * and decode slice header */
    if(s->codec_id==AV_CODEC_ID_MPEG4 && s->studio_profile) {
        align_get_bits(&s->gb);

        while (get_bits_left(&s->gb) >= 32 && show_bits_long(&s->gb, 32) != SLICE_START_CODE) {
            get_bits(&s->gb, 8);
        }

        if (get_bits_left(&s->gb) >= 32 && show_bits_long(&s->gb, 32) == SLICE_START_CODE)
            return get_bits_count(&s->gb);
        else
            return -1;
    }

    if(s->codec_id==AV_CODEC_ID_MPEG4){
        skip_bits1(&s->gb);
        align_get_bits(&s->gb);
    }

    if(show_bits(&s->gb, 16)==0){
        pos= get_bits_count(&s->gb);
        if(CONFIG_MPEG4_DECODER && s->codec_id==AV_CODEC_ID_MPEG4)
            ret= ff_mpeg4_decode_video_packet_header(s->avctx->priv_data);
        else
            ret= h263_decode_gob_header(s);
        if(ret>=0)
            return pos;
    }
    //OK, it's not where it is supposed to be ...
    s->gb= s->last_resync_gb;
    align_get_bits(&s->gb);
    left= get_bits_left(&s->gb);

    for(;left>16+1+5+5; left-=8){
        if(show_bits(&s->gb, 16)==0){
            GetBitContext bak= s->gb;

            pos= get_bits_count(&s->gb);
            if(CONFIG_MPEG4_DECODER && s->codec_id==AV_CODEC_ID_MPEG4)
                ret= ff_mpeg4_decode_video_packet_header(s->avctx->priv_data);
            else
                ret= h263_decode_gob_header(s);
            if(ret>=0)
                return pos;

            s->gb= bak;
        }
        skip_bits(&s->gb, 8);
    }

    return -1;
}