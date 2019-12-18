#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_6__ {unsigned int n_sb_blocks; TYPE_5__* sb_blocks; void* sb_entries; } ;
typedef  TYPE_1__ VividasDemuxContext ;
typedef  int /*<<< orphan*/  VIV_SB_entry ;
typedef  int /*<<< orphan*/  VIV_SB_block ;
struct TYPE_8__ {scalar_t__ size; scalar_t__ n_packets; scalar_t__ packet_offset; scalar_t__ byte_offset; } ;
struct TYPE_7__ {int /*<<< orphan*/  pb; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ INT_MAX ; 
 void* av_calloc (int,int) ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (TYPE_5__**) ; 
 int /*<<< orphan*/ * avio_alloc_context (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_r8 (int /*<<< orphan*/ *) ; 
 scalar_t__ avio_size (int /*<<< orphan*/ ) ; 
 void* ffio_read_varlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int track_index(VividasDemuxContext *viv, AVFormatContext *s, uint8_t *buf, unsigned size)
{
    int64_t off;
    int64_t poff;
    int maxnp=0;
    AVIOContext *pb;
    int i;
    int64_t filesize = avio_size(s->pb);

    pb = avio_alloc_context(buf, size, 0, NULL, NULL, NULL, NULL);
    if (!pb)
        return AVERROR(ENOMEM);

    ffio_read_varlen(pb); // track_index_len
    avio_r8(pb); // 'c'
    viv->n_sb_blocks = ffio_read_varlen(pb);
    if (viv->n_sb_blocks < 0 || viv->n_sb_blocks > size / 2)
        goto error;
    viv->sb_blocks = av_calloc(viv->n_sb_blocks, sizeof(VIV_SB_block));
    if (!viv->sb_blocks) {
        viv->n_sb_blocks = 0;
        av_free(pb);
        return AVERROR(ENOMEM);
    }

    off = 0;
    poff = 0;

    for (i = 0; i < viv->n_sb_blocks; i++) {
        uint64_t size_tmp      = ffio_read_varlen(pb);
        uint64_t n_packets_tmp = ffio_read_varlen(pb);

        if (size_tmp > INT_MAX || n_packets_tmp > INT_MAX)
            goto error;

        viv->sb_blocks[i].byte_offset = off;
        viv->sb_blocks[i].packet_offset = poff;

        viv->sb_blocks[i].size = size_tmp;
        viv->sb_blocks[i].n_packets = n_packets_tmp;

        off += viv->sb_blocks[i].size;
        poff += viv->sb_blocks[i].n_packets;

        if (maxnp < viv->sb_blocks[i].n_packets)
            maxnp = viv->sb_blocks[i].n_packets;
    }

    if (filesize > 0 && poff > filesize)
        goto error;

    viv->sb_entries = av_calloc(maxnp, sizeof(VIV_SB_entry));
    av_free(pb);

    return 0;
error:
    av_free(pb);
    viv->n_sb_blocks = 0;
    av_freep(&viv->sb_blocks);
    return AVERROR_INVALIDDATA;
}