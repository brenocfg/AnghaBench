#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_10__ {int timeline_start_pos; int /*<<< orphan*/  thumbnail; int /*<<< orphan*/  st_pairs; int /*<<< orphan*/  sp_pairs; } ;
typedef  TYPE_1__ WtvContext ;
struct TYPE_11__ {int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int WTV_SECTOR_BITS ; 
 int /*<<< orphan*/  WTV_TABLE_0_ENTRIES_LEGACY_ATTRIB ; 
 int /*<<< orphan*/  WTV_TABLE_0_ENTRIES_TIME ; 
 int /*<<< orphan*/  WTV_TABLE_0_REDIRECTOR_LEGACY_ATTRIB ; 
 int /*<<< orphan*/  WTV_TIMELINE ; 
 int /*<<< orphan*/  WTV_TIMELINE_TABLE_0_ENTRIES_EVENTS ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ finish_file (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int write_root_table (TYPE_2__*,int) ; 
 int /*<<< orphan*/  write_table_entries_attrib (TYPE_2__*) ; 
 int /*<<< orphan*/  write_table_entries_events (TYPE_2__*) ; 
 int /*<<< orphan*/  write_table_entries_time (TYPE_2__*) ; 
 int /*<<< orphan*/  write_table_redirector_legacy_attrib (TYPE_2__*) ; 

__attribute__((used)) static int write_trailer(AVFormatContext *s)
{
    WtvContext *wctx = s->priv_data;
    AVIOContext *pb = s->pb;
    int root_size;
    int64_t sector_pos;
    int64_t start_pos, file_end_pos;

    if (finish_file(s, WTV_TIMELINE, wctx->timeline_start_pos) < 0)
        return -1;

    start_pos = avio_tell(pb);
    write_table_entries_events(s);
    if (finish_file(s, WTV_TIMELINE_TABLE_0_ENTRIES_EVENTS, start_pos) < 0)
        return -1;

    start_pos = avio_tell(pb);
    write_table_entries_attrib(s);
    if (finish_file(s, WTV_TABLE_0_ENTRIES_LEGACY_ATTRIB, start_pos) < 0)
        return -1;

    start_pos = avio_tell(pb);
    write_table_redirector_legacy_attrib(s);
    if (finish_file(s, WTV_TABLE_0_REDIRECTOR_LEGACY_ATTRIB, start_pos) < 0)
        return -1;

    start_pos = avio_tell(pb);
    write_table_entries_time(s);
    if (finish_file(s, WTV_TABLE_0_ENTRIES_TIME, start_pos) < 0)
        return -1;

    // write root table
    sector_pos = avio_tell(pb);
    root_size = write_root_table(s, sector_pos);

    file_end_pos = avio_tell(pb);
    // update root value
    avio_seek(pb, 0x30, SEEK_SET);
    avio_wl32(pb, root_size);
    avio_seek(pb, 4, SEEK_CUR);
    avio_wl32(pb, sector_pos >> WTV_SECTOR_BITS);
    avio_seek(pb, 0x5c, SEEK_SET);
    avio_wl32(pb, file_end_pos >> WTV_SECTOR_BITS);

    avio_flush(pb);

    av_free(wctx->sp_pairs);
    av_free(wctx->st_pairs);
    av_packet_unref(&wctx->thumbnail);
    return 0;
}