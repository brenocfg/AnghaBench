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
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_10__ {int /*<<< orphan*/  stream_index; int /*<<< orphan*/  data; } ;
struct TYPE_9__ {int /*<<< orphan*/  index; } ;
struct TYPE_8__ {scalar_t__ timestamp; int* buf; scalar_t__ len; scalar_t__ pos; int /*<<< orphan*/ * dyn_buf; } ;
typedef  TYPE_1__ PayloadContext ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVPacket ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EIO ; 
 int RTP_FLAG_MARKER ; 
 int /*<<< orphan*/  av_freep (int**) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int av_new_packet (TYPE_3__*,int) ; 
 scalar_t__ avio_close_dyn_buf (int /*<<< orphan*/ *,int**) ; 
 int avio_open_dyn_buf (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int const*,int) ; 
 int /*<<< orphan*/  ffio_free_dyn_buf (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int latm_parse_packet(AVFormatContext *ctx, PayloadContext *data,
                             AVStream *st, AVPacket *pkt, uint32_t *timestamp,
                             const uint8_t *buf, int len, uint16_t seq,
                             int flags)
{
    int ret, cur_len;

    if (buf) {
        if (!data->dyn_buf || data->timestamp != *timestamp) {
            av_freep(&data->buf);
            ffio_free_dyn_buf(&data->dyn_buf);

            data->timestamp = *timestamp;
            if ((ret = avio_open_dyn_buf(&data->dyn_buf)) < 0)
                return ret;
        }
        avio_write(data->dyn_buf, buf, len);

        if (!(flags & RTP_FLAG_MARKER))
            return AVERROR(EAGAIN);
        av_freep(&data->buf);
        data->len = avio_close_dyn_buf(data->dyn_buf, &data->buf);
        data->dyn_buf = NULL;
        data->pos = 0;
    }

    if (!data->buf) {
        av_log(ctx, AV_LOG_ERROR, "No data available yet\n");
        return AVERROR(EIO);
    }

    cur_len = 0;
    while (data->pos < data->len) {
        uint8_t val = data->buf[data->pos++];
        cur_len += val;
        if (val != 0xff)
            break;
    }
    if (data->pos + cur_len > data->len) {
        av_log(ctx, AV_LOG_ERROR, "Malformed LATM packet\n");
        return AVERROR(EIO);
    }

    if ((ret = av_new_packet(pkt, cur_len)) < 0)
        return ret;
    memcpy(pkt->data, data->buf + data->pos, cur_len);
    data->pos += cur_len;
    pkt->stream_index = st->index;
    return data->pos < data->len;
}