#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_17__ {int nb_streams; int ist_index; } ;
struct TYPE_14__ {scalar_t__ last_pts; scalar_t__ end_pts; TYPE_2__* frame; } ;
struct TYPE_16__ {size_t file_index; int nb_filters; TYPE_4__** filters; TYPE_3__ sub2video; TYPE_1__* st; } ;
struct TYPE_15__ {int /*<<< orphan*/  filter; } ;
struct TYPE_13__ {int /*<<< orphan*/ * data; } ;
struct TYPE_12__ {int /*<<< orphan*/  time_base; } ;
typedef  TYPE_5__ InputStream ;
typedef  TYPE_6__ InputFile ;

/* Variables and functions */
 scalar_t__ INT64_MAX ; 
 scalar_t__ av_buffersrc_get_nb_failed_requests (int /*<<< orphan*/ ) ; 
 scalar_t__ av_rescale_q (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__** input_files ; 
 TYPE_5__** input_streams ; 
 int /*<<< orphan*/  sub2video_push_ref (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  sub2video_update (TYPE_5__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sub2video_heartbeat(InputStream *ist, int64_t pts)
{
    InputFile *infile = input_files[ist->file_index];
    int i, j, nb_reqs;
    int64_t pts2;

    /* When a frame is read from a file, examine all sub2video streams in
       the same file and send the sub2video frame again. Otherwise, decoded
       video frames could be accumulating in the filter graph while a filter
       (possibly overlay) is desperately waiting for a subtitle frame. */
    for (i = 0; i < infile->nb_streams; i++) {
        InputStream *ist2 = input_streams[infile->ist_index + i];
        if (!ist2->sub2video.frame)
            continue;
        /* subtitles seem to be usually muxed ahead of other streams;
           if not, subtracting a larger time here is necessary */
        pts2 = av_rescale_q(pts, ist->st->time_base, ist2->st->time_base) - 1;
        /* do not send the heartbeat frame if the subtitle is already ahead */
        if (pts2 <= ist2->sub2video.last_pts)
            continue;
        if (pts2 >= ist2->sub2video.end_pts ||
            (!ist2->sub2video.frame->data[0] && ist2->sub2video.end_pts < INT64_MAX))
            sub2video_update(ist2, NULL);
        for (j = 0, nb_reqs = 0; j < ist2->nb_filters; j++)
            nb_reqs += av_buffersrc_get_nb_failed_requests(ist2->filters[j]->filter);
        if (nb_reqs)
            sub2video_push_ref(ist2, pts2);
    }
}