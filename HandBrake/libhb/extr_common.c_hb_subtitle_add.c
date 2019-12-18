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
struct TYPE_9__ {int /*<<< orphan*/  list_subtitle; } ;
typedef  TYPE_1__ hb_title_t ;
struct TYPE_11__ {scalar_t__* name; int /*<<< orphan*/ * src_filename; } ;
struct TYPE_10__ {int track; scalar_t__ out_track; TYPE_3__ config; } ;
typedef  TYPE_2__ hb_subtitle_t ;
typedef  TYPE_3__ hb_subtitle_config_t ;
struct TYPE_12__ {int /*<<< orphan*/  list_subtitle; TYPE_1__* title; } ;
typedef  TYPE_4__ hb_job_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_list_add (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ hb_list_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_list_item (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* hb_subtitle_copy (int /*<<< orphan*/ ) ; 
 scalar_t__* strdup (scalar_t__*) ; 

int hb_subtitle_add(const hb_job_t * job, const hb_subtitle_config_t * subtitlecfg, int track)
{
    hb_title_t *title = job->title;
    hb_subtitle_t *subtitle;

    subtitle = hb_subtitle_copy( hb_list_item( title->list_subtitle, track ) );
    if( subtitle == NULL )
    {
        /* We fail! */
        return 0;
    }

    // "track" in title->list_audio is an index into the source's tracks.
    // "track" in job->list_audio is an index into title->list_audio
    subtitle->track = track;
    subtitle->config = *subtitlecfg;
    if (subtitlecfg->name != NULL && subtitlecfg->name[0] != 0)
    {
        subtitle->config.name = strdup(subtitlecfg->name);
    }
    else
    {
        subtitle->config.name = NULL;
    }
    subtitle->config.src_filename = NULL;
    subtitle->out_track = hb_list_count(job->list_subtitle) + 1;
    hb_list_add(job->list_subtitle, subtitle);
    return 1;
}