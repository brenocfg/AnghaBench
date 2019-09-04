#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  codec_type; } ;
struct TYPE_12__ {TYPE_2__** streams; TYPE_4__* priv_data; int /*<<< orphan*/ * pb; } ;
struct TYPE_11__ {int master_index_max_size; } ;
struct TYPE_8__ {int /*<<< orphan*/  indx_start; } ;
struct TYPE_10__ {TYPE_1__ indexes; } ;
struct TYPE_9__ {TYPE_3__* priv_data; TYPE_6__* codecpar; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVIStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVIContext ;
typedef  TYPE_5__ AVFormatContext ;
typedef  TYPE_6__ AVCodecParameters ;

/* Variables and functions */
 int /*<<< orphan*/  avi_stream2fourcc (unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wl16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wl64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_end_tag (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_start_tag (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_odml_master(AVFormatContext *s, int stream_index)
{
    AVIOContext *pb = s->pb;
    AVIContext *avi = s->priv_data;
    AVStream *st = s->streams[stream_index];
    AVCodecParameters *par = st->codecpar;
    AVIStream *avist = st->priv_data;
    unsigned char tag[5];
    int j;

    /* Starting to lay out AVI OpenDML master index.
        * We want to make it JUNK entry for now, since we'd
        * like to get away without making AVI an OpenDML one
        * for compatibility reasons. */
    avist->indexes.indx_start = ff_start_tag(pb, "JUNK");
    avio_wl16(pb, 4);   /* wLongsPerEntry */
    avio_w8(pb, 0);     /* bIndexSubType (0 == frame index) */
    avio_w8(pb, 0);     /* bIndexType (0 == AVI_INDEX_OF_INDEXES) */
    avio_wl32(pb, 0);   /* nEntriesInUse (will fill out later on) */
    ffio_wfourcc(pb, avi_stream2fourcc(tag, stream_index, par->codec_type));
                        /* dwChunkId */
    avio_wl64(pb, 0);   /* dwReserved[3] */
    avio_wl32(pb, 0);   /* Must be 0.    */
    for (j = 0; j < avi->master_index_max_size * 2; j++)
        avio_wl64(pb, 0);
    ff_end_tag(pb, avist->indexes.indx_start);
}