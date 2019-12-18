#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_21__ {TYPE_1__* internal; } ;
struct TYPE_20__ {int size; int /*<<< orphan*/  data; } ;
struct TYPE_19__ {int buf_size; int /*<<< orphan*/ * buf; } ;
struct TYPE_18__ {int request_probe; scalar_t__ probe_packets; int /*<<< orphan*/  index; TYPE_2__* codecpar; TYPE_4__ probe_data; } ;
struct TYPE_17__ {scalar_t__ codec_id; } ;
struct TYPE_16__ {scalar_t__ raw_packet_buffer_remaining_size; } ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVProbeData ;
typedef  TYPE_5__ AVPacket ;
typedef  TYPE_6__ AVFormatContext ;

/* Variables and functions */
 int AVPROBE_PADDING_SIZE ; 
 int AVPROBE_SCORE_STREAM_RETRY ; 
 scalar_t__ AV_CODEC_ID_NONE ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ av_log2 (int) ; 
 int /*<<< orphan*/ * av_realloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  force_codec_ids (TYPE_6__*,TYPE_3__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int set_codec_from_probe_data (TYPE_6__*,TYPE_3__*,TYPE_4__*) ; 

__attribute__((used)) static int probe_codec(AVFormatContext *s, AVStream *st, const AVPacket *pkt)
{
    if (st->request_probe>0) {
        AVProbeData *pd = &st->probe_data;
        int end;
        av_log(s, AV_LOG_DEBUG, "probing stream %d pp:%d\n", st->index, st->probe_packets);
        --st->probe_packets;

        if (pkt) {
            uint8_t *new_buf = av_realloc(pd->buf, pd->buf_size+pkt->size+AVPROBE_PADDING_SIZE);
            if (!new_buf) {
                av_log(s, AV_LOG_WARNING,
                       "Failed to reallocate probe buffer for stream %d\n",
                       st->index);
                goto no_packet;
            }
            pd->buf = new_buf;
            memcpy(pd->buf + pd->buf_size, pkt->data, pkt->size);
            pd->buf_size += pkt->size;
            memset(pd->buf + pd->buf_size, 0, AVPROBE_PADDING_SIZE);
        } else {
no_packet:
            st->probe_packets = 0;
            if (!pd->buf_size) {
                av_log(s, AV_LOG_WARNING,
                       "nothing to probe for stream %d\n", st->index);
            }
        }

        end=    s->internal->raw_packet_buffer_remaining_size <= 0
                || st->probe_packets<= 0;

        if (end || av_log2(pd->buf_size) != av_log2(pd->buf_size - pkt->size)) {
            int score = set_codec_from_probe_data(s, st, pd);
            if (    (st->codecpar->codec_id != AV_CODEC_ID_NONE && score > AVPROBE_SCORE_STREAM_RETRY)
                || end) {
                pd->buf_size = 0;
                av_freep(&pd->buf);
                st->request_probe = -1;
                if (st->codecpar->codec_id != AV_CODEC_ID_NONE) {
                    av_log(s, AV_LOG_DEBUG, "probed stream %d\n", st->index);
                } else
                    av_log(s, AV_LOG_WARNING, "probed stream %d failed\n", st->index);
            }
            force_codec_ids(s, st);
        }
    }
    return 0;
}