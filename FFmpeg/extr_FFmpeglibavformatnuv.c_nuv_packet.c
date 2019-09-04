#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  void* uint64_t ;
typedef  int nuv_frametype ;
struct TYPE_13__ {int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_12__ {int /*<<< orphan*/  stream_index; void* pts; void* pos; int /*<<< orphan*/  flags; int /*<<< orphan*/  data; } ;
struct TYPE_11__ {int /*<<< orphan*/  a_id; int /*<<< orphan*/  v_id; scalar_t__ rtjpg_video; } ;
typedef  TYPE_1__ NUVContext ;
typedef  TYPE_2__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 void* AV_RL32 (int*) ; 
 int /*<<< orphan*/  EIO ; 
 int HDRSIZE ; 
#define  NUV_AUDIO 131 
#define  NUV_EXTRADATA 130 
#define  NUV_SEEKP 129 
#define  NUV_VIDEO 128 
 int PKTSIZE (void*) ; 
 int av_get_packet (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int av_new_packet (TYPE_2__*,int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_2__*) ; 
 int /*<<< orphan*/  av_shrink_packet (TYPE_2__*,int) ; 
 int /*<<< orphan*/  avio_feof (int /*<<< orphan*/ *) ; 
 int avio_read (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 void* avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int nuv_packet(AVFormatContext *s, AVPacket *pkt)
{
    NUVContext *ctx = s->priv_data;
    AVIOContext *pb = s->pb;
    uint8_t hdr[HDRSIZE];
    nuv_frametype frametype;
    int ret, size;

    while (!avio_feof(pb)) {
        int copyhdrsize = ctx->rtjpg_video ? HDRSIZE : 0;
        uint64_t pos    = avio_tell(pb);

        ret = avio_read(pb, hdr, HDRSIZE);
        if (ret < HDRSIZE)
            return ret < 0 ? ret : AVERROR(EIO);

        frametype = hdr[0];
        size      = PKTSIZE(AV_RL32(&hdr[8]));

        switch (frametype) {
        case NUV_EXTRADATA:
            if (!ctx->rtjpg_video) {
                avio_skip(pb, size);
                break;
            }
        case NUV_VIDEO:
            if (ctx->v_id < 0) {
                av_log(s, AV_LOG_ERROR, "Video packet in file without video stream!\n");
                avio_skip(pb, size);
                break;
            }
            ret = av_new_packet(pkt, copyhdrsize + size);
            if (ret < 0)
                return ret;

            pkt->pos          = pos;
            pkt->flags       |= hdr[2] == 0 ? AV_PKT_FLAG_KEY : 0;
            pkt->pts          = AV_RL32(&hdr[4]);
            pkt->stream_index = ctx->v_id;
            memcpy(pkt->data, hdr, copyhdrsize);
            ret = avio_read(pb, pkt->data + copyhdrsize, size);
            if (ret < 0) {
                av_packet_unref(pkt);
                return ret;
            }
            if (ret < size)
                av_shrink_packet(pkt, copyhdrsize + ret);
            return 0;
        case NUV_AUDIO:
            if (ctx->a_id < 0) {
                av_log(s, AV_LOG_ERROR, "Audio packet in file without audio stream!\n");
                avio_skip(pb, size);
                break;
            }
            ret               = av_get_packet(pb, pkt, size);
            pkt->flags       |= AV_PKT_FLAG_KEY;
            pkt->pos          = pos;
            pkt->pts          = AV_RL32(&hdr[4]);
            pkt->stream_index = ctx->a_id;
            if (ret < 0)
                return ret;
            return 0;
        case NUV_SEEKP:
            // contains no data, size value is invalid
            break;
        default:
            avio_skip(pb, size);
            break;
        }
    }

    return AVERROR(EIO);
}