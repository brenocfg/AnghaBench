#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_17__ {int /*<<< orphan*/  pb; TYPE_3__** streams; TYPE_2__* priv_data; } ;
struct TYPE_16__ {scalar_t__ discard; TYPE_1__* priv_data; } ;
struct TYPE_15__ {size_t audio_stream_num; scalar_t__ old_format; scalar_t__ audio_pkt_cnt; } ;
struct TYPE_14__ {int coded_framesize; int sub_packet_h; int /*<<< orphan*/  audio_framesize; } ;
typedef  TYPE_1__ RMStream ;
typedef  TYPE_2__ RMDemuxContext ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AVDISCARD_ALL ; 
 scalar_t__ AVDISCARD_NONKEY ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AVINDEX_KEYFRAME ; 
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  EIO ; 
 int RAW_PACKET_SIZE ; 
 int /*<<< orphan*/  av_add_index_entry (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ ) ; 
 int ff_rm_parse_packet (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*,TYPE_1__*,int,int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ) ; 
 int ff_rm_retrieve_cache (TYPE_4__*,int /*<<< orphan*/ ,TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int rm_sync (TYPE_4__*,int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rm_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    RMDemuxContext *rm = s->priv_data;
    AVStream *st = NULL; // init to silence compiler warning
    int i, len, res, seq = 1;
    int64_t timestamp, pos;
    int flags;

    for (;;) {
        if (rm->audio_pkt_cnt) {
            // If there are queued audio packet return them first
            st = s->streams[rm->audio_stream_num];
            res = ff_rm_retrieve_cache(s, s->pb, st, st->priv_data, pkt);
            if(res < 0)
                return res;
            flags = 0;
        } else {
            if (rm->old_format) {
                RMStream *ast;

                st = s->streams[0];
                ast = st->priv_data;
                timestamp = AV_NOPTS_VALUE;
                len = !ast->audio_framesize ? RAW_PACKET_SIZE :
                    ast->coded_framesize * ast->sub_packet_h / 2;
                flags = (seq++ == 1) ? 2 : 0;
                pos = avio_tell(s->pb);
            } else {
                len = rm_sync(s, &timestamp, &flags, &i, &pos);
                if (len > 0)
                    st = s->streams[i];
            }

            if (avio_feof(s->pb))
                return AVERROR_EOF;
            if (len <= 0)
                return AVERROR(EIO);

            res = ff_rm_parse_packet (s, s->pb, st, st->priv_data, len, pkt,
                                      &seq, flags, timestamp);
            if (res < -1)
                return res;
            if((flags&2) && (seq&0x7F) == 1)
                av_add_index_entry(st, pos, timestamp, 0, 0, AVINDEX_KEYFRAME);
            if (res)
                continue;
        }

        if(  (st->discard >= AVDISCARD_NONKEY && !(flags&2))
           || st->discard >= AVDISCARD_ALL){
            av_packet_unref(pkt);
        } else
            break;
    }

    return 0;
}