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
typedef  int uint8_t ;
typedef  int nuv_frametype ;
typedef  scalar_t__ int64_t ;
struct TYPE_6__ {int /*<<< orphan*/ * streams; int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_5__ {int v_id; int a_id; } ;
typedef  TYPE_1__ NUVContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVINDEX_KEYFRAME ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 scalar_t__ AV_RL32 (int*) ; 
 int HDRSIZE ; 
#define  NUV_AUDIO 130 
#define  NUV_SEEKP 129 
#define  NUV_VIDEO 128 
 int PKTSIZE (scalar_t__) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_add_index_entry (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_feof (int /*<<< orphan*/ *) ; 
 int avio_read (int /*<<< orphan*/ *,int*,int) ; 
 scalar_t__ avio_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nuv_resync (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static int64_t nuv_read_dts(AVFormatContext *s, int stream_index,
                            int64_t *ppos, int64_t pos_limit)
{
    NUVContext *ctx = s->priv_data;
    AVIOContext *pb = s->pb;
    uint8_t hdr[HDRSIZE];
    nuv_frametype frametype;
    int size, key, idx;
    int64_t pos, dts;

    if (avio_seek(pb, *ppos, SEEK_SET) < 0)
        return AV_NOPTS_VALUE;

    if (!nuv_resync(s, pos_limit))
        return AV_NOPTS_VALUE;

    while (!avio_feof(pb) && avio_tell(pb) < pos_limit) {
        if (avio_read(pb, hdr, HDRSIZE) < HDRSIZE)
            return AV_NOPTS_VALUE;
        frametype = hdr[0];
        size = PKTSIZE(AV_RL32(&hdr[8]));
        switch (frametype) {
            case NUV_SEEKP:
                break;
            case NUV_AUDIO:
            case NUV_VIDEO:
                if (frametype == NUV_VIDEO) {
                    idx = ctx->v_id;
                    key = hdr[2] == 0;
                } else {
                    idx = ctx->a_id;
                    key = 1;
                }
                if (stream_index == idx) {

                    pos = avio_tell(s->pb) - HDRSIZE;
                    dts = AV_RL32(&hdr[4]);

                    // TODO - add general support in av_gen_search, so it adds positions after reading timestamps
                    av_add_index_entry(s->streams[stream_index], pos, dts, size + HDRSIZE, 0,
                            key ? AVINDEX_KEYFRAME : 0);

                    *ppos = pos;
                    return dts;
                }
            default:
                avio_skip(pb, size);
                break;
        }
    }
    return AV_NOPTS_VALUE;
}