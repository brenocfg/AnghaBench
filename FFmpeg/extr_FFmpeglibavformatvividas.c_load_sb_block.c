#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {int n_sb_entries; size_t current_sb; scalar_t__ current_sb_entry; TYPE_2__* sb_entries; TYPE_1__* sb_blocks; int /*<<< orphan*/ * sb_pb; int /*<<< orphan*/ * sb_buf; int /*<<< orphan*/  sb_key; } ;
typedef  TYPE_3__ VividasDemuxContext ;
struct TYPE_10__ {int /*<<< orphan*/  pb; } ;
struct TYPE_8__ {int /*<<< orphan*/  flag; int /*<<< orphan*/  size; } ;
struct TYPE_7__ {int n_packets; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * avio_alloc_context (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_r8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffio_read_varlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * read_sb_block (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void load_sb_block(AVFormatContext *s, VividasDemuxContext *viv, unsigned expected_size)
{
    uint32_t size = 0;
    int i;
    AVIOContext *pb = 0;

    if (viv->sb_pb) {
        av_free(viv->sb_pb);
        viv->sb_pb = NULL;
    }

    if (viv->sb_buf)
        av_free(viv->sb_buf);

    viv->sb_buf = read_sb_block(s->pb, &size, &viv->sb_key, expected_size);
    if (!viv->sb_buf) {
        return;
    }

    pb = avio_alloc_context(viv->sb_buf, size, 0, NULL, NULL, NULL, NULL);
    if (!pb)
        return;

    viv->sb_pb = pb;

    avio_r8(pb); //  'S'
    avio_r8(pb); //  'B'
    ffio_read_varlen(pb); //  size
    avio_r8(pb); //  junk
    ffio_read_varlen(pb); // first packet

    viv->n_sb_entries = viv->sb_blocks[viv->current_sb].n_packets;

    for (i = 0; i < viv->n_sb_entries; i++) {
        viv->sb_entries[i].size = ffio_read_varlen(pb);
        viv->sb_entries[i].flag = avio_r8(pb);
    }

    ffio_read_varlen(pb);
    avio_r8(pb);

    viv->current_sb_entry = 0;
}