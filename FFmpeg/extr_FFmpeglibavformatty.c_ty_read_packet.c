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
typedef  scalar_t__ int64_t ;
struct TYPE_11__ {scalar_t__ rec_size; int rec_type; } ;
typedef  TYPE_1__ TyRecHdr ;
struct TYPE_13__ {int /*<<< orphan*/ * pb; TYPE_2__* priv_data; } ;
struct TYPE_12__ {size_t cur_rec; size_t num_recs; scalar_t__ cur_chunk_pos; TYPE_1__* rec_hdrs; scalar_t__ first_chunk; } ;
typedef  TYPE_2__ TYDemuxContext ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
#define  AUDIO_ID 129 
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 scalar_t__ CHUNK_SIZE ; 
#define  VIDEO_ID 128 
 scalar_t__ avio_feof (int /*<<< orphan*/ *) ; 
 int demux_audio (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int demux_video (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_dlog (TYPE_3__*,char*,int) ; 
 scalar_t__ get_chunk (TYPE_3__*) ; 

__attribute__((used)) static int ty_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    TYDemuxContext *ty = s->priv_data;
    AVIOContext *pb = s->pb;
    TyRecHdr *rec;
    int64_t rec_size = 0;
    int ret = 0;

    if (avio_feof(pb))
        return AVERROR_EOF;

    while (ret <= 0) {
        if (!ty->rec_hdrs || ty->first_chunk || ty->cur_rec >= ty->num_recs) {
            if (get_chunk(s) < 0 || ty->num_recs <= 0)
                return AVERROR_EOF;
        }

        rec = &ty->rec_hdrs[ty->cur_rec];
        rec_size = rec->rec_size;
        ty->cur_rec++;

        if (rec_size <= 0)
            continue;

        if (ty->cur_chunk_pos + rec->rec_size > CHUNK_SIZE)
            return AVERROR_INVALIDDATA;

        if (avio_feof(pb))
            return AVERROR_EOF;

        switch (rec->rec_type) {
        case VIDEO_ID:
            ret = demux_video(s, rec, pkt);
            break;
        case AUDIO_ID:
            ret = demux_audio(s, rec, pkt);
            break;
        default:
            ff_dlog(s, "Invalid record type 0x%02x\n", rec->rec_type);
        case 0x01:
        case 0x02:
        case 0x03: /* TiVo data services */
        case 0x05: /* unknown, but seen regularly */
            ty->cur_chunk_pos += rec->rec_size;
            break;
        }
    }

    return 0;
}