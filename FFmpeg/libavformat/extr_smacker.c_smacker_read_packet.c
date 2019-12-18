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
typedef  void* uint8_t ;
typedef  long long uint32_t ;
struct TYPE_10__ {int /*<<< orphan*/  pb; TYPE_1__* priv_data; } ;
struct TYPE_9__ {int* data; scalar_t__ stream_index; size_t pts; int size; } ;
struct TYPE_8__ {size_t cur_frame; size_t frames; int curstream; int nextpos; int* frm_size; int* frm_flags; void** pal; void*** bufs; long long* buf_sizes; scalar_t__* stream_id; scalar_t__* indexes; scalar_t__ videoindex; size_t* aud_pts; } ;
typedef  TYPE_1__ SmackerContext ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_RL32 (void**) ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int INT_MAX ; 
 int SMACKER_PAL ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ av_new_packet (TYPE_2__*,int) ; 
 int av_reallocp (void***,long long) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ ) ; 
 int avio_r8 (int /*<<< orphan*/ ) ; 
 int avio_read (int /*<<< orphan*/ ,void**,int) ; 
 long long avio_rl32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int avio_tell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void**,void**,int) ; 
 void** smk_pal ; 

__attribute__((used)) static int smacker_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    SmackerContext *smk = s->priv_data;
    int flags;
    int ret;
    int i;
    int frame_size = 0;
    int palchange = 0;

    if (avio_feof(s->pb) || smk->cur_frame >= smk->frames)
        return AVERROR_EOF;

    /* if we demuxed all streams, pass another frame */
    if(smk->curstream < 0) {
        avio_seek(s->pb, smk->nextpos, 0);
        frame_size = smk->frm_size[smk->cur_frame] & (~3);
        flags = smk->frm_flags[smk->cur_frame];
        /* handle palette change event */
        if(flags & SMACKER_PAL){
            int size, sz, t, off, j, pos;
            uint8_t *pal = smk->pal;
            uint8_t oldpal[768];

            memcpy(oldpal, pal, 768);
            size = avio_r8(s->pb);
            size = size * 4 - 1;
            if(size + 1 > frame_size)
                return AVERROR_INVALIDDATA;
            frame_size -= size;
            frame_size--;
            sz = 0;
            pos = avio_tell(s->pb) + size;
            while(sz < 256){
                t = avio_r8(s->pb);
                if(t & 0x80){ /* skip palette entries */
                    sz += (t & 0x7F) + 1;
                    pal += ((t & 0x7F) + 1) * 3;
                } else if(t & 0x40){ /* copy with offset */
                    off = avio_r8(s->pb);
                    j = (t & 0x3F) + 1;
                    if (off + j > 0x100) {
                        av_log(s, AV_LOG_ERROR,
                               "Invalid palette update, offset=%d length=%d extends beyond palette size\n",
                               off, j);
                        return AVERROR_INVALIDDATA;
                    }
                    off *= 3;
                    while(j-- && sz < 256) {
                        *pal++ = oldpal[off + 0];
                        *pal++ = oldpal[off + 1];
                        *pal++ = oldpal[off + 2];
                        sz++;
                        off += 3;
                    }
                } else { /* new entries */
                    *pal++ = smk_pal[t];
                    *pal++ = smk_pal[avio_r8(s->pb) & 0x3F];
                    *pal++ = smk_pal[avio_r8(s->pb) & 0x3F];
                    sz++;
                }
            }
            avio_seek(s->pb, pos, 0);
            palchange |= 1;
        }
        flags >>= 1;
        smk->curstream = -1;
        /* if audio chunks are present, put them to stack and retrieve later */
        for(i = 0; i < 7; i++) {
            if(flags & 1) {
                uint32_t size;
                int err;

                size = avio_rl32(s->pb) - 4;
                if (!size || size + 4LL > frame_size) {
                    av_log(s, AV_LOG_ERROR, "Invalid audio part size\n");
                    return AVERROR_INVALIDDATA;
                }
                frame_size -= size;
                frame_size -= 4;
                smk->curstream++;
                if ((err = av_reallocp(&smk->bufs[smk->curstream], size)) < 0) {
                    smk->buf_sizes[smk->curstream] = 0;
                    return err;
                }
                smk->buf_sizes[smk->curstream] = size;
                ret = avio_read(s->pb, smk->bufs[smk->curstream], size);
                if(ret != size)
                    return AVERROR(EIO);
                smk->stream_id[smk->curstream] = smk->indexes[i];
            }
            flags >>= 1;
        }
        if (frame_size < 0 || frame_size >= INT_MAX/2)
            return AVERROR_INVALIDDATA;
        if (av_new_packet(pkt, frame_size + 769))
            return AVERROR(ENOMEM);
        if(smk->frm_size[smk->cur_frame] & 1)
            palchange |= 2;
        pkt->data[0] = palchange;
        memcpy(pkt->data + 1, smk->pal, 768);
        ret = avio_read(s->pb, pkt->data + 769, frame_size);
        if(ret != frame_size)
            return AVERROR(EIO);
        pkt->stream_index = smk->videoindex;
        pkt->pts          = smk->cur_frame;
        pkt->size = ret + 769;
        smk->cur_frame++;
        smk->nextpos = avio_tell(s->pb);
    } else {
        if (smk->stream_id[smk->curstream] < 0 || !smk->bufs[smk->curstream])
            return AVERROR_INVALIDDATA;
        if (av_new_packet(pkt, smk->buf_sizes[smk->curstream]))
            return AVERROR(ENOMEM);
        memcpy(pkt->data, smk->bufs[smk->curstream], smk->buf_sizes[smk->curstream]);
        pkt->size = smk->buf_sizes[smk->curstream];
        pkt->stream_index = smk->stream_id[smk->curstream];
        pkt->pts = smk->aud_pts[smk->curstream];
        smk->aud_pts[smk->curstream] += AV_RL32(pkt->data);
        smk->curstream--;
    }

    return 0;
}