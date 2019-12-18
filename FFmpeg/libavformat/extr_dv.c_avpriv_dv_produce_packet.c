#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  void* int64_t ;
struct TYPE_21__ {int frame_size; int height; } ;
struct TYPE_20__ {int* data; int size; int /*<<< orphan*/  pts; int /*<<< orphan*/  stream_index; int /*<<< orphan*/  flags; void* pos; } ;
struct TYPE_19__ {int ach; int abytes; int** audio_buf; int /*<<< orphan*/  frames; TYPE_4__* vst; TYPE_3__* audio_pkt; TYPE_9__* sys; TYPE_2__** ast; } ;
struct TYPE_18__ {int /*<<< orphan*/  index; } ;
struct TYPE_17__ {int size; int pts; void* pos; } ;
struct TYPE_16__ {TYPE_1__* codecpar; } ;
struct TYPE_15__ {int bit_rate; } ;
typedef  TYPE_5__ DVDemuxContext ;
typedef  TYPE_6__ AVPacket ;

/* Variables and functions */
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int DV_PROFILE_BYTES ; 
 TYPE_9__* av_dv_frame_profile (TYPE_9__*,int*,int) ; 
 int /*<<< orphan*/  av_init_packet (TYPE_6__*) ; 
 int /*<<< orphan*/  dv_extract_audio (int*,int**,TYPE_9__*) ; 
 int dv_extract_audio_info (TYPE_5__*,int*) ; 
 int dv_extract_video_info (TYPE_5__*,int*) ; 

int avpriv_dv_produce_packet(DVDemuxContext *c, AVPacket *pkt,
                             uint8_t *buf, int buf_size, int64_t pos)
{
    int size, i;
    uint8_t *ppcm[5] = { 0 };

    if (buf_size < DV_PROFILE_BYTES ||
        !(c->sys = av_dv_frame_profile(c->sys, buf, buf_size)) ||
        buf_size < c->sys->frame_size) {
        return -1;   /* Broken frame, or not enough data */
    }

    /* Queueing audio packet */
    /* FIXME: in case of no audio/bad audio we have to do something */
    size = dv_extract_audio_info(c, buf);
    for (i = 0; i < c->ach; i++) {
        c->audio_pkt[i].pos  = pos;
        c->audio_pkt[i].size = size;
        c->audio_pkt[i].pts  = c->abytes * 30000 * 8 /
                               c->ast[i]->codecpar->bit_rate;
        ppcm[i] = c->audio_buf[i];
    }
    if (c->ach)
        dv_extract_audio(buf, ppcm, c->sys);

    /* We work with 720p frames split in half, thus even frames have
     * channels 0,1 and odd 2,3. */
    if (c->sys->height == 720) {
        if (buf[1] & 0x0C) {
            c->audio_pkt[2].size = c->audio_pkt[3].size = 0;
        } else {
            c->audio_pkt[0].size = c->audio_pkt[1].size = 0;
            c->abytes           += size;
        }
    } else {
        c->abytes += size;
    }

    /* Now it's time to return video packet */
    size = dv_extract_video_info(c, buf);
    av_init_packet(pkt);
    pkt->data         = buf;
    pkt->pos          = pos;
    pkt->size         = size;
    pkt->flags       |= AV_PKT_FLAG_KEY;
    pkt->stream_index = c->vst->index;
    pkt->pts          = c->frames;

    c->frames++;

    return size;
}