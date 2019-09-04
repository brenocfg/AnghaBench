#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_14__ {TYPE_4__* priv_data; } ;
struct TYPE_13__ {int flags; } ;
struct TYPE_12__ {int count; size_t duration; } ;
struct TYPE_11__ {int entry; TYPE_1__* cluster; } ;
struct TYPE_10__ {size_t cts; } ;
typedef  TYPE_2__ MOVTrack ;
typedef  TYPE_3__ MOVStts ;
typedef  TYPE_4__ MOVMuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int FF_MOV_FLAG_NEGATIVE_CTS_OFFSETS ; 
 int /*<<< orphan*/  av_free (TYPE_3__*) ; 
 TYPE_3__* av_malloc_array (int,int) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb24 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int mov_write_ctts_tag(AVFormatContext *s, AVIOContext *pb, MOVTrack *track)
{
    MOVMuxContext *mov = s->priv_data;
    MOVStts *ctts_entries;
    uint32_t entries = 0;
    uint32_t atom_size;
    int i;

    ctts_entries = av_malloc_array((track->entry + 1), sizeof(*ctts_entries)); /* worst case */
    if (!ctts_entries)
        return AVERROR(ENOMEM);
    ctts_entries[0].count = 1;
    ctts_entries[0].duration = track->cluster[0].cts;
    for (i = 1; i < track->entry; i++) {
        if (track->cluster[i].cts == ctts_entries[entries].duration) {
            ctts_entries[entries].count++; /* compress */
        } else {
            entries++;
            ctts_entries[entries].duration = track->cluster[i].cts;
            ctts_entries[entries].count = 1;
        }
    }
    entries++; /* last one */
    atom_size = 16 + (entries * 8);
    avio_wb32(pb, atom_size); /* size */
    ffio_wfourcc(pb, "ctts");
    if (mov->flags & FF_MOV_FLAG_NEGATIVE_CTS_OFFSETS)
        avio_w8(pb, 1); /* version */
    else
        avio_w8(pb, 0); /* version */
    avio_wb24(pb, 0); /* flags */
    avio_wb32(pb, entries); /* entry count */
    for (i = 0; i < entries; i++) {
        avio_wb32(pb, ctts_entries[i].count);
        avio_wb32(pb, ctts_entries[i].duration);
    }
    av_free(ctts_entries);
    return atom_size;
}