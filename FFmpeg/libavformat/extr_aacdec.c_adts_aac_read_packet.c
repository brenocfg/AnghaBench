#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  pb; } ;
struct TYPE_11__ {int size; scalar_t__ data; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int ADTS_HEADER_SIZE ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int AV_RB16 (scalar_t__) ; 
 int AV_RB32 (scalar_t__) ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ID3v2_DEFAULT_MAGIC ; 
 int ID3v2_HEADER_SIZE ; 
 int adts_aac_resync (TYPE_2__*) ; 
 int av_append_packet (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  av_assert2 (int) ; 
 int av_get_packet (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_1__*) ; 
 int /*<<< orphan*/  ff_id3v2_match (scalar_t__,int /*<<< orphan*/ ) ; 
 int handle_id3 (TYPE_2__*,TYPE_1__*) ; 

__attribute__((used)) static int adts_aac_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    int ret, fsize;

retry:
    ret = av_get_packet(s->pb, pkt, ADTS_HEADER_SIZE);
    if (ret < 0)
        return ret;

    if (ret < ADTS_HEADER_SIZE) {
        av_packet_unref(pkt);
        return AVERROR(EIO);
    }

    if ((AV_RB16(pkt->data) >> 4) != 0xfff) {
        // Parse all the ID3 headers between frames
        int append = ID3v2_HEADER_SIZE - ADTS_HEADER_SIZE;

        av_assert2(append > 0);
        ret = av_append_packet(s->pb, pkt, append);
        if (ret != append) {
            av_packet_unref(pkt);
            return AVERROR(EIO);
        }
        if (!ff_id3v2_match(pkt->data, ID3v2_DEFAULT_MAGIC)) {
            av_packet_unref(pkt);
            ret = adts_aac_resync(s);
        } else
            ret = handle_id3(s, pkt);
        if (ret < 0)
            return ret;

        goto retry;
    }

    fsize = (AV_RB32(pkt->data + 3) >> 13) & 0x1FFF;
    if (fsize < ADTS_HEADER_SIZE) {
        av_packet_unref(pkt);
        return AVERROR_INVALIDDATA;
    }

    ret = av_append_packet(s->pb, pkt, fsize - pkt->size);
    if (ret < 0)
        av_packet_unref(pkt);

    return ret;
}