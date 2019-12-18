#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  pb; TYPE_2__** streams; TYPE_1__* priv_data; } ;
struct TYPE_13__ {scalar_t__ timestamp; int /*<<< orphan*/  pos; int /*<<< orphan*/  size; } ;
struct TYPE_12__ {size_t stream_index; scalar_t__ pts; int /*<<< orphan*/  pos; } ;
struct TYPE_11__ {size_t nb_index_entries; TYPE_4__* index_entries; } ;
struct TYPE_10__ {size_t next_video_index; size_t total_vframes; size_t video_stream_index; size_t next_audio_index; size_t total_aframes; size_t audio_stream_index; scalar_t__ is_audio_present; } ;
typedef  TYPE_1__ IFVContext ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVIndexEntry ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int av_get_packet (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ ) ; 
 scalar_t__ avio_rl32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ ,int) ; 
 int read_index (TYPE_5__*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int ifv_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    IFVContext *ifv = s->priv_data;
    AVStream *st;
    AVIndexEntry *ev, *ea, *e_next;
    int ret;

    ev = ea = e_next = NULL;

    if (ifv->next_video_index < ifv->total_vframes) {
        st = s->streams[ifv->video_stream_index];
        if (ifv->next_video_index < st->nb_index_entries)
            e_next = ev = &st->index_entries[ifv->next_video_index];
    }

    if (ifv->is_audio_present &&
        ifv->next_audio_index < ifv->total_aframes) {
        st = s->streams[ifv->audio_stream_index];
        if (ifv->next_audio_index < st->nb_index_entries) {
            ea = &st->index_entries[ifv->next_audio_index];
            if (!ev || ea->timestamp < ev->timestamp)
                e_next = ea;
        }
    }

    if (!ev) {
        if (ifv->is_audio_present && !ea) {
            /*read new video and audio indexes*/

            ifv->next_video_index = ifv->total_vframes;
            ifv->next_audio_index = ifv->total_aframes;

            avio_skip(s->pb, 0x1c);
            ifv->total_vframes += avio_rl32(s->pb);
            ifv->total_aframes += avio_rl32(s->pb);
            avio_skip(s->pb, 0xc);

            if (avio_feof(s->pb))
                return AVERROR_EOF;

            ret = read_index(s, AVMEDIA_TYPE_VIDEO, ifv->next_video_index);
            if (ret < 0)
                return ret;

            ret = read_index(s, AVMEDIA_TYPE_AUDIO, ifv->next_audio_index);
            if (ret < 0)
                return ret;

            return 0;

        } else if (!ifv->is_audio_present) {
            /*read new video index*/

            ifv->next_video_index = ifv->total_vframes;

            avio_skip(s->pb, 0x1c);
            ifv->total_vframes += avio_rl32(s->pb);
            avio_skip(s->pb, 0x10);

            if (avio_feof(s->pb))
                return AVERROR_EOF;

            ret = read_index(s, AVMEDIA_TYPE_VIDEO, ifv->next_video_index);
            if (ret < 0)
                return ret;

            return 0;
        }
    }

    if (!e_next) return AVERROR_EOF;

    avio_seek(s->pb, e_next->pos, SEEK_SET);
    ret = av_get_packet(s->pb, pkt, e_next->size);
    if (ret < 0)
        return ret;

    if (e_next == ev) {
        ifv->next_video_index++;
        pkt->stream_index = ifv->video_stream_index;
    } else {
        ifv->next_audio_index++;
        pkt->stream_index = ifv->audio_stream_index;
    }

    pkt->pts = e_next->timestamp;
    pkt->pos = e_next->pos;

    return 0;
}