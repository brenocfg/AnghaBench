#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_11__ {int count; int duration; } ;
struct TYPE_10__ {int sample_count; int entry; int /*<<< orphan*/  audio_vbr; TYPE_1__* par; } ;
struct TYPE_9__ {scalar_t__ codec_type; } ;
typedef  TYPE_2__ MOVTrack ;
typedef  TYPE_3__ MOVStts ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_free (TYPE_3__*) ; 
 TYPE_3__* av_malloc (int) ; 
 TYPE_3__* av_malloc_array (int,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int get_cluster_duration (TYPE_2__*,int) ; 

__attribute__((used)) static int mov_write_stts_tag(AVIOContext *pb, MOVTrack *track)
{
    MOVStts *stts_entries = NULL;
    uint32_t entries = -1;
    uint32_t atom_size;
    int i;

    if (track->par->codec_type == AVMEDIA_TYPE_AUDIO && !track->audio_vbr) {
        stts_entries = av_malloc(sizeof(*stts_entries)); /* one entry */
        if (!stts_entries)
            return AVERROR(ENOMEM);
        stts_entries[0].count = track->sample_count;
        stts_entries[0].duration = 1;
        entries = 1;
    } else {
        if (track->entry) {
            stts_entries = av_malloc_array(track->entry, sizeof(*stts_entries)); /* worst case */
            if (!stts_entries)
                return AVERROR(ENOMEM);
        }
        for (i = 0; i < track->entry; i++) {
            int duration = get_cluster_duration(track, i);
            if (i && duration == stts_entries[entries].duration) {
                stts_entries[entries].count++; /* compress */
            } else {
                entries++;
                stts_entries[entries].duration = duration;
                stts_entries[entries].count = 1;
            }
        }
        entries++; /* last one */
    }
    atom_size = 16 + (entries * 8);
    avio_wb32(pb, atom_size); /* size */
    ffio_wfourcc(pb, "stts");
    avio_wb32(pb, 0); /* version & flags */
    avio_wb32(pb, entries); /* entry count */
    for (i = 0; i < entries; i++) {
        avio_wb32(pb, stts_entries[i].count);
        avio_wb32(pb, stts_entries[i].duration);
    }
    av_free(stts_entries);
    return atom_size;
}