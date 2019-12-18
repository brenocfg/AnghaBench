#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_9__ {int /*<<< orphan*/  stream_index; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {int /*<<< orphan*/  index; TYPE_1__* codecpar; } ;
struct TYPE_7__ {scalar_t__ codec_type; } ;
typedef  int /*<<< orphan*/  PayloadContext ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVPacket ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 unsigned int AV_RB32 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ av_new_packet (TYPE_3__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int mpeg_parse_packet(AVFormatContext *ctx, PayloadContext *data,
                             AVStream *st, AVPacket *pkt, uint32_t *timestamp,
                             const uint8_t *buf, int len, uint16_t seq,
                             int flags)
{
    unsigned int h;
    if (len <= 4)
        return AVERROR_INVALIDDATA;
    h    = AV_RB32(buf);
    buf += 4;
    len -= 4;
    if (st->codecpar->codec_type == AVMEDIA_TYPE_VIDEO && h & (1 << 26)) {
        /* MPEG-2 */
        if (len <= 4)
            return AVERROR_INVALIDDATA;
        buf += 4;
        len -= 4;
    }
    if (av_new_packet(pkt, len) < 0)
        return AVERROR(ENOMEM);
    memcpy(pkt->data, buf, len);
    pkt->stream_index = st->index;
    return 0;
}