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
struct TYPE_6__ {size_t num_entries; scalar_t__ segment_offset; TYPE_2__* entries; } ;
typedef  TYPE_1__ mkv_cues ;
struct TYPE_7__ {int stream_idx; int tracknum; scalar_t__ duration; scalar_t__ relative_pos; scalar_t__ cluster_pos; scalar_t__ pts; } ;
typedef  TYPE_2__ mkv_cuepoint ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_2__* av_realloc_array (TYPE_2__*,size_t,int) ; 

__attribute__((used)) static int mkv_add_cuepoint(mkv_cues *cues, int stream, int tracknum, int64_t ts,
                            int64_t cluster_pos, int64_t relative_pos, int64_t duration)
{
    mkv_cuepoint *entries = cues->entries;

    if (ts < 0)
        return 0;

    entries = av_realloc_array(entries, cues->num_entries + 1, sizeof(mkv_cuepoint));
    if (!entries)
        return AVERROR(ENOMEM);
    cues->entries = entries;

    cues->entries[cues->num_entries].pts           = ts;
    cues->entries[cues->num_entries].stream_idx    = stream;
    cues->entries[cues->num_entries].tracknum      = tracknum;
    cues->entries[cues->num_entries].cluster_pos   = cluster_pos - cues->segment_offset;
    cues->entries[cues->num_entries].relative_pos  = relative_pos;
    cues->entries[cues->num_entries++].duration    = duration;

    return 0;
}