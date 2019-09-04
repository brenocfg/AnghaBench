#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_6__ {int cur_chunk; int* chunk; int num_recs; int seq_rec; int cur_chunk_pos; int /*<<< orphan*/  rec_hdrs; scalar_t__ first_chunk; scalar_t__ cur_rec; } ;
typedef  TYPE_1__ TYDemuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 scalar_t__ AV_RB32 (int*) ; 
 int CHUNK_SIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ TIVO_PES_FILEID ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ *) ; 
 int avio_read (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  ff_dlog (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  parse_chunk_headers (int*,int) ; 
 int /*<<< orphan*/  parse_master (TYPE_2__*) ; 

__attribute__((used)) static int get_chunk(AVFormatContext *s)
{
    TYDemuxContext *ty = s->priv_data;
    AVIOContext *pb = s->pb;
    int read_size, num_recs;

    ff_dlog(s, "parsing ty chunk #%d\n", ty->cur_chunk);

    /* if we have left-over filler space from the last chunk, get that */
    if (avio_feof(pb))
        return AVERROR_EOF;

    /* read the TY packet header */
    read_size = avio_read(pb, ty->chunk, CHUNK_SIZE);
    ty->cur_chunk++;

    if ((read_size < 4) || (AV_RB32(ty->chunk) == 0)) {
        return AVERROR_EOF;
    }

    /* check if it's a PART Header */
    if (AV_RB32(ty->chunk) == TIVO_PES_FILEID) {
        parse_master(s); /* parse master chunk */
        return get_chunk(s);
    }

    /* number of records in chunk (8- or 16-bit number) */
    if (ty->chunk[3] & 0x80) {
        /* 16 bit rec cnt */
        ty->num_recs = num_recs = (ty->chunk[1] << 8) + ty->chunk[0];
        ty->seq_rec = (ty->chunk[3] << 8) + ty->chunk[2];
        if (ty->seq_rec != 0xffff) {
            ty->seq_rec &= ~0x8000;
        }
    } else {
        /* 8 bit reclen - TiVo 1.3 format */
        ty->num_recs = num_recs = ty->chunk[0];
        ty->seq_rec = ty->chunk[1];
    }
    ty->cur_rec = 0;
    ty->first_chunk = 0;

    ff_dlog(s, "chunk has %d records\n", num_recs);
    ty->cur_chunk_pos = 4;

    av_freep(&ty->rec_hdrs);

    if (num_recs * 16 >= CHUNK_SIZE - 4)
        return AVERROR_INVALIDDATA;

    ty->rec_hdrs = parse_chunk_headers(ty->chunk + 4, num_recs);
    if (!ty->rec_hdrs)
        return AVERROR(ENOMEM);
    ty->cur_chunk_pos += 16 * num_recs;

    return 0;
}