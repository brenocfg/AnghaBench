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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct TYPE_7__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  stream_index; } ;
struct TYPE_6__ {int /*<<< orphan*/  index; } ;
typedef  int /*<<< orphan*/  PayloadContext ;
typedef  TYPE_1__ AVStream ;
typedef  TYPE_2__ AVPacket ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_RB16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ av_new_packet (TYPE_2__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

int ff_h263_handle_packet(AVFormatContext *ctx, PayloadContext *data,
                          AVStream *st, AVPacket *pkt, uint32_t *timestamp,
                          const uint8_t *buf, int len, uint16_t seq, int flags)
{
    uint8_t *ptr;
    uint16_t header;
    int startcode, vrc, picture_header;

    if (len < 2) {
        av_log(ctx, AV_LOG_ERROR, "Too short H.263 RTP packet\n");
        return AVERROR_INVALIDDATA;
    }

    /* Decode the 16 bit H.263+ payload header, as described in section
     * 5.1 of RFC 4629. The fields of this header are:
     * - 5 reserved bits, should be ignored.
     * - One bit (P, startcode), indicating a picture start, picture segment
     *   start or video sequence end. If set, two zero bytes should be
     *   prepended to the payload.
     * - One bit (V, vrc), indicating the presence of an 8 bit Video
     *   Redundancy Coding field after this 16 bit header.
     * - 6 bits (PLEN, picture_header), the length (in bytes) of an extra
     *   picture header, following the VRC field.
     * - 3 bits (PEBIT), the number of bits to ignore of the last byte
     *   of the extra picture header. (Not used at the moment.)
     */
    header = AV_RB16(buf);
    startcode      = (header & 0x0400) >> 9;
    vrc            =  header & 0x0200;
    picture_header = (header & 0x01f8) >> 3;
    buf += 2;
    len -= 2;

    if (vrc) {
        /* Skip VRC header if present, not used at the moment. */
        buf += 1;
        len -= 1;
    }
    if (picture_header) {
        /* Skip extra picture header if present, not used at the moment. */
        buf += picture_header;
        len -= picture_header;
    }

    if (len < 0) {
        av_log(ctx, AV_LOG_ERROR, "Too short H.263 RTP packet\n");
        return AVERROR_INVALIDDATA;
    }

    if (av_new_packet(pkt, len + startcode)) {
        av_log(ctx, AV_LOG_ERROR, "Out of memory\n");
        return AVERROR(ENOMEM);
    }
    pkt->stream_index = st->index;
    ptr = pkt->data;

    if (startcode) {
        *ptr++ = 0;
        *ptr++ = 0;
    }
    memcpy(ptr, buf, len);

    return 0;
}