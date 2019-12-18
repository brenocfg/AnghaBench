#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_10__ {TYPE_1__* item; } ;
struct TYPE_9__ {scalar_t__ sidx_pts; } ;
struct TYPE_8__ {int nb_stream_info; TYPE_2__* stream_info; } ;
typedef  TYPE_2__ MOVFragmentStreamInfo ;
typedef  TYPE_3__ MOVFragmentIndex ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 TYPE_2__* get_frag_stream_info (TYPE_3__*,int,int) ; 
 scalar_t__ get_stream_info_time (TYPE_2__*) ; 

__attribute__((used)) static int64_t get_frag_time(MOVFragmentIndex *frag_index,
                             int index, int track_id)
{
    MOVFragmentStreamInfo * frag_stream_info;
    int64_t timestamp;
    int i;

    if (track_id >= 0) {
        frag_stream_info = get_frag_stream_info(frag_index, index, track_id);
        return frag_stream_info->sidx_pts;
    }

    for (i = 0; i < frag_index->item[index].nb_stream_info; i++) {
        frag_stream_info = &frag_index->item[index].stream_info[i];
        timestamp = get_stream_info_time(frag_stream_info);
        if (timestamp != AV_NOPTS_VALUE)
            return timestamp;
    }
    return AV_NOPTS_VALUE;
}