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
typedef  scalar_t__ int64_t ;
struct TYPE_6__ {int /*<<< orphan*/ * streams; TYPE_1__* priv_data; int /*<<< orphan*/ * pb; } ;
struct TYPE_5__ {int continue_pes; } ;
typedef  TYPE_1__ PVAContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVINDEX_KEYFRAME ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  EIO ; 
 int PVA_AUDIO_PAYLOAD ; 
 int PVA_MAGIC ; 
 int PVA_MAX_PAYLOAD_LENGTH ; 
 int PVA_VIDEO_PAYLOAD ; 
 int /*<<< orphan*/  av_add_index_entry (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ *) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int avio_rb16 (int /*<<< orphan*/ *) ; 
 int avio_rb24 (int /*<<< orphan*/ *) ; 
 scalar_t__ avio_rb32 (int /*<<< orphan*/ *) ; 
 int avio_read (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ *) ; 
 scalar_t__ ff_parse_pes_pts (unsigned char*) ; 
 int /*<<< orphan*/  pva_log (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int read_part_of_packet(AVFormatContext *s, int64_t *pts,
                               int *len, int *strid, int read_packet) {
    AVIOContext *pb = s->pb;
    PVAContext *pvactx = s->priv_data;
    int syncword, streamid, reserved, flags, length, pts_flag;
    int64_t pva_pts = AV_NOPTS_VALUE, startpos;
    int ret;

recover:
    startpos = avio_tell(pb);

    syncword = avio_rb16(pb);
    streamid = avio_r8(pb);
    avio_r8(pb);               /* counter not used */
    reserved = avio_r8(pb);
    flags    = avio_r8(pb);
    length   = avio_rb16(pb);

    pts_flag = flags & 0x10;

    if (syncword != PVA_MAGIC) {
        pva_log(s, AV_LOG_ERROR, "invalid syncword\n");
        return AVERROR(EIO);
    }
    if (streamid != PVA_VIDEO_PAYLOAD && streamid != PVA_AUDIO_PAYLOAD) {
        pva_log(s, AV_LOG_ERROR, "invalid streamid\n");
        return AVERROR(EIO);
    }
    if (reserved != 0x55) {
        pva_log(s, AV_LOG_WARNING, "expected reserved byte to be 0x55\n");
    }
    if (length > PVA_MAX_PAYLOAD_LENGTH) {
        pva_log(s, AV_LOG_ERROR, "invalid payload length %u\n", length);
        return AVERROR(EIO);
    }

    if (streamid == PVA_VIDEO_PAYLOAD && pts_flag) {
        pva_pts = avio_rb32(pb);
        length -= 4;
    } else if (streamid == PVA_AUDIO_PAYLOAD) {
        /* PVA Audio Packets either start with a signaled PES packet or
         * are a continuation of the previous PES packet. New PES packets
         * always start at the beginning of a PVA Packet, never somewhere in
         * the middle. */
        if (!pvactx->continue_pes) {
            int pes_signal, pes_header_data_length, pes_packet_length,
                pes_flags;
            unsigned char pes_header_data[256];

            pes_signal             = avio_rb24(pb);
            avio_r8(pb);
            pes_packet_length      = avio_rb16(pb);
            pes_flags              = avio_rb16(pb);
            pes_header_data_length = avio_r8(pb);

            if (avio_feof(pb)) {
                return AVERROR_EOF;
            }

            if (pes_signal != 1 || pes_header_data_length == 0) {
                pva_log(s, AV_LOG_WARNING, "expected non empty signaled PES packet, "
                                          "trying to recover\n");
                avio_skip(pb, length - 9);
                if (!read_packet)
                    return AVERROR(EIO);
                goto recover;
            }

            ret = avio_read(pb, pes_header_data, pes_header_data_length);
            if (ret != pes_header_data_length)
                return ret < 0 ? ret : AVERROR_INVALIDDATA;
            length -= 9 + pes_header_data_length;

            pes_packet_length -= 3 + pes_header_data_length;

            pvactx->continue_pes = pes_packet_length;

            if (pes_flags & 0x80 && (pes_header_data[0] & 0xf0) == 0x20) {
                if (pes_header_data_length < 5) {
                    pva_log(s, AV_LOG_ERROR, "header too short\n");
                    avio_skip(pb, length);
                    return AVERROR_INVALIDDATA;
                }
                pva_pts = ff_parse_pes_pts(pes_header_data);
            }
        }

        pvactx->continue_pes -= length;

        if (pvactx->continue_pes < 0) {
            pva_log(s, AV_LOG_WARNING, "audio data corruption\n");
            pvactx->continue_pes = 0;
        }
    }

    if (pva_pts != AV_NOPTS_VALUE)
        av_add_index_entry(s->streams[streamid-1], startpos, pva_pts, 0, 0, AVINDEX_KEYFRAME);

    *pts   = pva_pts;
    *len   = length;
    *strid = streamid;
    return 0;
}