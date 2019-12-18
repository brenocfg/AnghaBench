#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_18__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int int64_t ;
struct TYPE_26__ {int nb_streams; TYPE_2__** streams; TYPE_6__* priv_data; TYPE_4__* pb; } ;
struct TYPE_25__ {int riff_id; int master_index_max_size; int /*<<< orphan*/  movi_list; } ;
struct TYPE_24__ {int pos; int flags; scalar_t__ len; } ;
struct TYPE_23__ {int seekable; } ;
struct TYPE_19__ {int master_odml_riff_id_base; int entry; } ;
struct TYPE_22__ {TYPE_18__ indexes; } ;
struct TYPE_21__ {TYPE_1__* codecpar; TYPE_3__* priv_data; } ;
struct TYPE_20__ {int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_3__ AVIStream ;
typedef  TYPE_4__ AVIOContext ;
typedef  TYPE_5__ AVIIentry ;
typedef  TYPE_6__ AVIContext ;
typedef  TYPE_7__ AVFormatContext ;

/* Variables and functions */
 int AVIO_SEEKABLE_NORMAL ; 
 int AVI_MASTER_INDEX_ENTRY_SIZE ; 
 int AVI_MASTER_INDEX_PREFIX_SIZE ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_assert1 (int) ; 
 TYPE_5__* avi_get_ientry (TYPE_18__*,int) ; 
 int /*<<< orphan*/  avi_stream2fourcc (char*,int,int /*<<< orphan*/ ) ; 
 int avio_tell (TYPE_4__*) ; 
 int /*<<< orphan*/  avio_w8 (TYPE_4__*,int) ; 
 int /*<<< orphan*/  avio_wl16 (TYPE_4__*,int) ; 
 int /*<<< orphan*/  avio_wl32 (TYPE_4__*,int) ; 
 int /*<<< orphan*/  avio_wl64 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffio_wfourcc (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  update_odml_entry (TYPE_7__*,int,int,int) ; 
 int /*<<< orphan*/  write_odml_master (TYPE_7__*,int) ; 

__attribute__((used)) static int avi_write_ix(AVFormatContext *s)
{
    AVIOContext *pb = s->pb;
    AVIContext *avi = s->priv_data;
    char tag[5];
    char ix_tag[] = "ix00";
    int i, j;

    av_assert0(pb->seekable & AVIO_SEEKABLE_NORMAL);

    for (i = 0; i < s->nb_streams; i++) {
        AVIStream *avist = s->streams[i]->priv_data;
        if (avi->riff_id - avist->indexes.master_odml_riff_id_base == avi->master_index_max_size) {
            int64_t pos;
            int size = AVI_MASTER_INDEX_PREFIX_SIZE + AVI_MASTER_INDEX_ENTRY_SIZE * avi->master_index_max_size;

            pos = avio_tell(pb);
            update_odml_entry(s, i, pos, size);
            write_odml_master(s, i);
            av_assert1(avio_tell(pb) - pos == size);
            avist->indexes.master_odml_riff_id_base = avi->riff_id - 1;
        }
        av_assert0(avi->riff_id - avist->indexes.master_odml_riff_id_base < avi->master_index_max_size);
    }

    for (i = 0; i < s->nb_streams; i++) {
        AVIStream *avist = s->streams[i]->priv_data;
        int64_t ix;

        avi_stream2fourcc(tag, i, s->streams[i]->codecpar->codec_type);
        ix_tag[3] = '0' + i;

        /* Writing AVI OpenDML leaf index chunk */
        ix = avio_tell(pb);
        ffio_wfourcc(pb, ix_tag);      /* ix?? */
        avio_wl32(pb, avist->indexes.entry * 8 + 24);
        /* chunk size */
        avio_wl16(pb, 2);           /* wLongsPerEntry */
        avio_w8(pb, 0);             /* bIndexSubType (0 == frame index) */
        avio_w8(pb, 1);             /* bIndexType (1 == AVI_INDEX_OF_CHUNKS) */
        avio_wl32(pb, avist->indexes.entry);
        /* nEntriesInUse */
        ffio_wfourcc(pb, tag);         /* dwChunkId */
        avio_wl64(pb, avi->movi_list); /* qwBaseOffset */
        avio_wl32(pb, 0);              /* dwReserved_3 (must be 0) */

        for (j = 0; j < avist->indexes.entry; j++) {
            AVIIentry *ie = avi_get_ientry(&avist->indexes, j);
            avio_wl32(pb, ie->pos + 8);
            avio_wl32(pb, ((uint32_t) ie->len & ~0x80000000) |
                          (ie->flags & 0x10 ? 0 : 0x80000000));
        }

        update_odml_entry(s, i, ix, avio_tell(pb) - ix);
    }
    return 0;
}