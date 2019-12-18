#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * pb; TYPE_2__* priv_data; } ;
struct TYPE_11__ {int size; int /*<<< orphan*/  flags; } ;
struct TYPE_10__ {int page; int record; int page_table_offset; TYPE_1__* pt; } ;
struct TYPE_9__ {int nb_records; scalar_t__ base_record; } ;
typedef  TYPE_1__ Page ;
typedef  TYPE_2__ AnmDemuxContext ;
typedef  TYPE_3__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  EIO ; 
 int MAX_PAGES ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int av_get_packet (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ *) ; 
 int avio_rl16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int avio_tell (int /*<<< orphan*/ *) ; 
 int find_record (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static int read_packet(AVFormatContext *s,
                       AVPacket *pkt)
{
    AnmDemuxContext *anm = s->priv_data;
    AVIOContext *pb = s->pb;
    Page *p;
    int tmp, record_size;

    if (avio_feof(s->pb))
        return AVERROR(EIO);

    if (anm->page < 0)
        return anm->page;

repeat:
    p = &anm->pt[anm->page];

    /* parse page header */
    if (anm->record < 0) {
        avio_seek(pb, anm->page_table_offset + MAX_PAGES*6 + (anm->page<<16), SEEK_SET);
        avio_skip(pb, 8 + 2*p->nb_records);
        anm->record = 0;
    }

    /* if we have fetched all records in this page, then find the
       next page and repeat */
    if (anm->record >= p->nb_records) {
        anm->page = find_record(anm, p->base_record + p->nb_records);
        if (anm->page < 0)
            return anm->page;
        anm->record = -1;
        goto repeat;
    }

    /* fetch record size */
    tmp = avio_tell(pb);
    avio_seek(pb, anm->page_table_offset + MAX_PAGES*6 + (anm->page<<16) +
              8 + anm->record * 2, SEEK_SET);
    record_size = avio_rl16(pb);
    avio_seek(pb, tmp, SEEK_SET);

    /* fetch record */
    pkt->size = av_get_packet(s->pb, pkt, record_size);
    if (pkt->size < 0)
        return pkt->size;
    if (p->base_record + anm->record == 0)
        pkt->flags |= AV_PKT_FLAG_KEY;

    anm->record++;
    return 0;
}