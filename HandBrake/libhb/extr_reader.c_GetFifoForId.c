#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ ** fifos; scalar_t__ start_found; TYPE_5__* job; } ;
typedef  TYPE_2__ hb_work_private_t ;
struct TYPE_10__ {int video_id; } ;
typedef  TYPE_3__ hb_title_t ;
struct TYPE_11__ {int id; int /*<<< orphan*/ * fifo_in; } ;
typedef  TYPE_4__ hb_subtitle_t ;
struct TYPE_12__ {int /*<<< orphan*/  list_audio; scalar_t__ indepth_scan; int /*<<< orphan*/  list_subtitle; int /*<<< orphan*/ * fifo_mpeg2; TYPE_3__* title; } ;
typedef  TYPE_5__ hb_job_t ;
typedef  int /*<<< orphan*/  hb_fifo_t ;
struct TYPE_8__ {int /*<<< orphan*/ * fifo_in; } ;
struct TYPE_13__ {int id; TYPE_1__ priv; } ;
typedef  TYPE_6__ hb_audio_t ;

/* Variables and functions */
 int hb_list_count (int /*<<< orphan*/ ) ; 
 void* hb_list_item (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static hb_fifo_t ** GetFifoForId( hb_work_private_t * r, int id )
{
    hb_job_t      * job = r->job;
    hb_title_t    * title = job->title;
    hb_audio_t    * audio;
    hb_subtitle_t * subtitle;
    int             i, n;

    if (id == title->video_id)
    {
        if (job->indepth_scan && r->start_found)
        {
            /*
             * Ditch the video here during the indepth scan until
             * we can improve the MPEG2 decode performance.
             *
             * But if we specify a stop frame, we must decode the
             * frames in order to count them.
             */
            return NULL;
        }
        else
        {
            r->fifos[0] = job->fifo_mpeg2;
            r->fifos[1] = NULL;
            return r->fifos;
        }
    }

    for (i = n = 0; i < hb_list_count( job->list_subtitle ); i++)
    {
        subtitle =  hb_list_item( job->list_subtitle, i );
        if (id == subtitle->id)
        {
            /* pass the subtitles to be processed */
            r->fifos[n++] = subtitle->fifo_in;
        }
    }
    if (n != 0)
    {
        r->fifos[n] = NULL;
        return r->fifos;
    }

    if (!job->indepth_scan)
    {
        for (i = n = 0; i < hb_list_count( job->list_audio ); i++)
        {
            audio = hb_list_item( job->list_audio, i );
            if (id == audio->id)
            {
                r->fifos[n++] = audio->priv.fifo_in;
            }
        }

        if (n != 0)
        {
            r->fifos[n] = NULL;
            return r->fifos;
        }
    }

    return NULL;
}