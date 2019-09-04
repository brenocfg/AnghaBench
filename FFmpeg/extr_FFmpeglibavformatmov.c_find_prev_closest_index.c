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
typedef  size_t int64_t ;
struct TYPE_12__ {scalar_t__ timestamp; int flags; } ;
struct TYPE_11__ {int nb_index_entries; TYPE_4__* index_entries; TYPE_2__* priv_data; } ;
struct TYPE_10__ {scalar_t__ dts_shift; } ;
struct TYPE_9__ {size_t count; size_t duration; } ;
typedef  TYPE_1__ MOVStts ;
typedef  TYPE_2__ MOVStreamContext ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVIndexEntry ;

/* Variables and functions */
 int AVINDEX_KEYFRAME ; 
 int AVSEEK_FLAG_ANY ; 
 int AVSEEK_FLAG_BACKWARD ; 
 int /*<<< orphan*/  av_assert0 (size_t*) ; 
 size_t av_index_search_timestamp (TYPE_3__*,size_t,int) ; 

__attribute__((used)) static int find_prev_closest_index(AVStream *st,
                                   AVIndexEntry *e_old,
                                   int nb_old,
                                   MOVStts* ctts_data,
                                   int64_t ctts_count,
                                   int64_t timestamp_pts,
                                   int flag,
                                   int64_t* index,
                                   int64_t* ctts_index,
                                   int64_t* ctts_sample)
{
    MOVStreamContext *msc = st->priv_data;
    AVIndexEntry *e_keep = st->index_entries;
    int nb_keep = st->nb_index_entries;
    int64_t i = 0;
    int64_t index_ctts_count;

    av_assert0(index);

    // If dts_shift > 0, then all the index timestamps will have to be offset by
    // at least dts_shift amount to obtain PTS.
    // Hence we decrement the searched timestamp_pts by dts_shift to find the closest index element.
    if (msc->dts_shift > 0) {
        timestamp_pts -= msc->dts_shift;
    }

    st->index_entries = e_old;
    st->nb_index_entries = nb_old;
    *index = av_index_search_timestamp(st, timestamp_pts, flag | AVSEEK_FLAG_BACKWARD);

    // Keep going backwards in the index entries until the timestamp is the same.
    if (*index >= 0) {
        for (i = *index; i > 0 && e_old[i].timestamp == e_old[i - 1].timestamp;
             i--) {
            if ((flag & AVSEEK_FLAG_ANY) ||
                (e_old[i - 1].flags & AVINDEX_KEYFRAME)) {
                *index = i - 1;
            }
        }
    }

    // If we have CTTS then refine the search, by searching backwards over PTS
    // computed by adding corresponding CTTS durations to index timestamps.
    if (ctts_data && *index >= 0) {
        av_assert0(ctts_index);
        av_assert0(ctts_sample);
        // Find out the ctts_index for the found frame.
        *ctts_index = 0;
        *ctts_sample = 0;
        for (index_ctts_count = 0; index_ctts_count < *index; index_ctts_count++) {
            if (*ctts_index < ctts_count) {
                (*ctts_sample)++;
                if (ctts_data[*ctts_index].count == *ctts_sample) {
                    (*ctts_index)++;
                    *ctts_sample = 0;
                }
            }
        }

        while (*index >= 0 && (*ctts_index) >= 0 && (*ctts_index) < ctts_count) {
            // Find a "key frame" with PTS <= timestamp_pts (So that we can decode B-frames correctly).
            // No need to add dts_shift to the timestamp here becase timestamp_pts has already been
            // compensated by dts_shift above.
            if ((e_old[*index].timestamp + ctts_data[*ctts_index].duration) <= timestamp_pts &&
                (e_old[*index].flags & AVINDEX_KEYFRAME)) {
                break;
            }

            (*index)--;
            if (*ctts_sample == 0) {
                (*ctts_index)--;
                if (*ctts_index >= 0)
                  *ctts_sample = ctts_data[*ctts_index].count - 1;
            } else {
                (*ctts_sample)--;
            }
        }
    }

    /* restore AVStream state*/
    st->index_entries = e_keep;
    st->nb_index_entries = nb_keep;
    return *index >= 0 ? 0 : -1;
}