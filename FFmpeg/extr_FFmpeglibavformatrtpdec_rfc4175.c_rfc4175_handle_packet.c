#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_7__ {int /*<<< orphan*/  index; } ;
struct TYPE_6__ {scalar_t__ timestamp; int* frame; int frame_size; int pgroup; int width; int xinc; } ;
typedef  TYPE_1__ PayloadContext ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  ENOMEM ; 
 int RTP_FLAG_MARKER ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int* av_malloc (int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int rfc4175_finalize_packet (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rfc4175_handle_packet(AVFormatContext *ctx, PayloadContext *data,
                                 AVStream *st, AVPacket *pkt, uint32_t *timestamp,
                                 const uint8_t * buf, int len,
                                 uint16_t seq, int flags)
{
    int length, line, offset, cont;
    const uint8_t *headers = buf + 2; /* skip extended seqnum */
    const uint8_t *payload = buf + 2;
    int payload_len = len - 2;
    int missed_last_packet = 0;

    uint8_t *dest;

    if (*timestamp != data->timestamp) {
        if (data->frame) {
            /*
             * if we're here, it means that two RTP packets didn't have the
             * same timestamp, which is a sign that they were packets from two
             * different frames, but we didn't get the flag RTP_FLAG_MARKER on
             * the first one of these frames (last packet of a frame).
             * Finalize the previous frame anyway by filling the AVPacket.
             */
            av_log(ctx, AV_LOG_ERROR, "Missed previous RTP Marker\n");
            missed_last_packet = 1;
            rfc4175_finalize_packet(data, pkt, st->index);
        }

        data->frame = av_malloc(data->frame_size);

        data->timestamp = *timestamp;

        if (!data->frame) {
            av_log(ctx, AV_LOG_ERROR, "Out of memory.\n");
            return AVERROR(ENOMEM);
        }
    }

    /*
     * looks for the 'Continuation bit' in scan lines' headers
     * to find where data start
     */
    do {
        if (payload_len < 6)
            return AVERROR_INVALIDDATA;

        cont = payload[4] & 0x80;
        payload += 6;
        payload_len -= 6;
    } while (cont);

    /* and now iterate over every scan lines */
    do {
        int copy_offset;

        if (payload_len < data->pgroup)
            return AVERROR_INVALIDDATA;

        length = (headers[0] << 8) | headers[1];
        line = ((headers[2] & 0x7f) << 8) | headers[3];
        offset = ((headers[4] & 0x7f) << 8) | headers[5];
        cont = headers[4] & 0x80;
        headers += 6;

        if (length % data->pgroup)
            return AVERROR_INVALIDDATA;

        if (length > payload_len)
            length = payload_len;

        /* prevent ill-formed packets to write after buffer's end */
        copy_offset = (line * data->width + offset) * data->pgroup / data->xinc;
        if (copy_offset + length > data->frame_size)
            return AVERROR_INVALIDDATA;

        dest = data->frame + copy_offset;
        memcpy(dest, payload, length);

        payload += length;
        payload_len -= length;
    } while (cont);

    if ((flags & RTP_FLAG_MARKER)) {
        return rfc4175_finalize_packet(data, pkt, st->index);
    } else if (missed_last_packet) {
        return 0;
    }

    return AVERROR(EAGAIN);
}