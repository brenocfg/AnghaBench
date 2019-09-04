#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_21__ {size_t audio_stream_idx; int frames; int ssnd; int form; scalar_t__ write_id3v2; TYPE_2__* pict_list; } ;
struct TYPE_20__ {int block_align; } ;
struct TYPE_19__ {TYPE_3__* pb; TYPE_1__** streams; TYPE_6__* priv_data; } ;
struct TYPE_18__ {int seekable; } ;
struct TYPE_17__ {int /*<<< orphan*/  pkt; struct TYPE_17__* next; } ;
struct TYPE_16__ {TYPE_5__* codecpar; } ;
typedef  TYPE_2__ AVPacketList ;
typedef  TYPE_3__ AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;
typedef  TYPE_5__ AVCodecParameters ;
typedef  TYPE_6__ AIFFOutputContext ;

/* Variables and functions */
 int AVIO_SEEKABLE_NORMAL ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_freep (TYPE_2__**) ; 
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_flush (TYPE_3__*) ; 
 int /*<<< orphan*/  avio_seek (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int avio_tell (TYPE_3__*) ; 
 int /*<<< orphan*/  avio_w8 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb32 (TYPE_3__*,int) ; 
 int put_id3v2_tags (TYPE_4__*,TYPE_6__*) ; 

__attribute__((used)) static int aiff_write_trailer(AVFormatContext *s)
{
    int ret;
    AVIOContext *pb = s->pb;
    AIFFOutputContext *aiff = s->priv_data;
    AVPacketList *pict_list = aiff->pict_list;
    AVCodecParameters *par = s->streams[aiff->audio_stream_idx]->codecpar;

    /* Chunks sizes must be even */
    int64_t file_size, end_size;
    end_size = file_size = avio_tell(pb);
    if (file_size & 1) {
        avio_w8(pb, 0);
        end_size++;
    }

    if (s->pb->seekable & AVIO_SEEKABLE_NORMAL) {
        /* Number of sample frames */
        avio_seek(pb, aiff->frames, SEEK_SET);
        avio_wb32(pb, (file_size - aiff->ssnd - 12) / par->block_align);

        /* Sound Data chunk size */
        avio_seek(pb, aiff->ssnd, SEEK_SET);
        avio_wb32(pb, file_size - aiff->ssnd - 4);

        /* return to the end */
        avio_seek(pb, end_size, SEEK_SET);

        /* Write ID3 tags */
        if (aiff->write_id3v2)
            if ((ret = put_id3v2_tags(s, aiff)) < 0)
                return ret;

        /* File length */
        file_size = avio_tell(pb);
        avio_seek(pb, aiff->form, SEEK_SET);
        avio_wb32(pb, file_size - aiff->form - 4);

        avio_flush(pb);
    }

    while (pict_list) {
        AVPacketList *next = pict_list->next;
        av_packet_unref(&pict_list->pkt);
        av_freep(&pict_list);
        pict_list = next;
    }

    return 0;
}