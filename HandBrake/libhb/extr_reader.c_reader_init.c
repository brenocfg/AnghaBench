#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_14__ {void* last_scr; } ;
struct TYPE_17__ {int chapter_end; int start_found; scalar_t__ duration; int splice_list_size; void* fifos; TYPE_3__* splice_list; TYPE_12__* title; int /*<<< orphan*/  pts_to_start; void* last_pts; TYPE_1__ demux; int /*<<< orphan*/  die; TYPE_7__* job; int /*<<< orphan*/  h; } ;
typedef  TYPE_4__ hb_work_private_t ;
struct TYPE_18__ {TYPE_4__* private_data; } ;
typedef  TYPE_5__ hb_work_object_t ;
struct TYPE_19__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_6__ hb_subtitle_t ;
struct TYPE_20__ {int chapter_end; scalar_t__ pts_to_start; scalar_t__ pts_to_stop; int frame_to_stop; int frame_to_start; int /*<<< orphan*/  list_audio; int /*<<< orphan*/  list_subtitle; TYPE_12__* title; int /*<<< orphan*/  die; int /*<<< orphan*/  h; } ;
typedef  TYPE_7__ hb_job_t ;
typedef  int /*<<< orphan*/  hb_fifo_t ;
struct TYPE_21__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_8__ hb_audio_t ;
typedef  int /*<<< orphan*/  buffer_splice_list_t ;
struct TYPE_16__ {int /*<<< orphan*/  id; } ;
struct TYPE_15__ {int den; int num; } ;
struct TYPE_13__ {int duration; int /*<<< orphan*/  video_id; int /*<<< orphan*/  list_chapter; TYPE_2__ vrate; } ;

/* Variables and functions */
 void* AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,scalar_t__) ; 
 void* calloc (int,int) ; 
 int chapter_end_pts (TYPE_12__*,int) ; 
 int hb_list_count (int /*<<< orphan*/ ) ; 
 void* hb_list_item (int /*<<< orphan*/ ,int) ; 
 scalar_t__ hb_reader_open (TYPE_4__*) ; 

__attribute__((used)) static int reader_init( hb_work_object_t * w, hb_job_t * job )
{
    hb_work_private_t * r;

    r = calloc( sizeof( hb_work_private_t ), 1 );
    w->private_data = r;

    r->h     = job->h;
    r->job   = job;
    r->title = job->title;
    r->die   = job->die;

    r->demux.last_scr = AV_NOPTS_VALUE;
    r->last_pts       = AV_NOPTS_VALUE;

    r->chapter_end = job->chapter_end;
    if (!job->pts_to_start)
    {
        r->start_found = 1;
    }
    else
    {
        // The frame at the actual start time may not be an i-frame
        // so can't be decoded without starting a little early.
        // sync.c will drop early frames.
        // Starting a little over 10 seconds early
        r->pts_to_start = MAX(0, job->pts_to_start - 1000000);
    }

    if (job->pts_to_stop > 0)
    {
        r->duration = job->pts_to_start + job->pts_to_stop;
    }
    else if (job->frame_to_stop)
    {
        int frames = job->frame_to_start + job->frame_to_stop;
        r->duration = (int64_t)frames * job->title->vrate.den * 90000 /
                                        job->title->vrate.num;
    }
    else
    {
        int count = hb_list_count(job->title->list_chapter);
        if (count == 0 || count <= job->chapter_end)
        {
            r->duration = job->title->duration;
        }
        else
        {
            r->duration = chapter_end_pts(job->title, job->chapter_end);
        }
    }

    // Count number of splice lists needed for merging buffers
    // that have been split
    int count = 1; // 1 for video
    count += hb_list_count( job->list_subtitle );
    count += hb_list_count( job->list_audio );
    r->splice_list_size = count;
    r->splice_list = calloc(count, sizeof(buffer_splice_list_t));

    // Initialize stream id's of splice lists
    int ii, jj = 0;
    r->splice_list[jj++].id = r->title->video_id;
    for (ii = 0; ii < hb_list_count(job->list_subtitle); ii++)
    {
        hb_subtitle_t * subtitle = hb_list_item(job->list_subtitle, ii);
        r->splice_list[jj++].id = subtitle->id;
    }
    for (ii = 0; ii < hb_list_count(job->list_audio); ii++)
    {
        hb_audio_t * audio = hb_list_item(job->list_audio, ii);
        r->splice_list[jj++].id = audio->id;
    }

    // count also happens to be the upper bound for the number of
    // fifos that will be needed (+1 for null terminator)
    r->fifos = calloc(count + 1, sizeof(hb_fifo_t*));

    // The stream needs to be open before starting the reader thead
    // to prevent a race with decoders that may share information
    // with the reader. Specifically avcodec needs this.
    if ( hb_reader_open( r ) )
    {
        return 1;
    }
    return 0;
}