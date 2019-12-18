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

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  list_audio; } ;
typedef  TYPE_5__ hb_title_t ;
struct TYPE_19__ {int /*<<< orphan*/  list_audio; TYPE_5__* title; } ;
typedef  TYPE_6__ hb_job_t ;
struct TYPE_17__ {scalar_t__* name; scalar_t__ track; } ;
struct TYPE_14__ {int /*<<< orphan*/  track; } ;
struct TYPE_16__ {TYPE_4__ out; TYPE_1__ in; } ;
struct TYPE_20__ {TYPE_3__ config; } ;
typedef  TYPE_7__ hb_audio_t ;
struct TYPE_15__ {int bitrate; int codec; int /*<<< orphan*/  track; } ;
struct TYPE_21__ {TYPE_4__ out; TYPE_2__ in; } ;
typedef  TYPE_8__ hb_audio_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_audio_close (TYPE_7__**) ; 
 TYPE_7__* hb_audio_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_list_add (int /*<<< orphan*/ ,TYPE_7__*) ; 
 scalar_t__ hb_list_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_list_item (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* strdup (scalar_t__*) ; 

int hb_audio_add(const hb_job_t * job, const hb_audio_config_t * audiocfg)
{
    hb_title_t *title = job->title;
    hb_audio_t *audio;

    audio = hb_audio_copy( hb_list_item( title->list_audio, audiocfg->in.track ) );
    if( audio == NULL )
    {
        /* We fail! */
        return 0;
    }

    if( (audiocfg->in.bitrate != -1) && (audiocfg->in.codec != 0xDEADBEEF) )
    {
        /* This most likely means the client didn't call hb_audio_config_init
         * so bail. */
        hb_audio_close(&audio);
        return 0;
    }

    /* Set the job's "in track" to the value passed in audiocfg.
     * HandBrakeCLI assumes this value is preserved in the jobs
     * audio list, but in.track in the title's audio list is not
     * required to be the same. */
    // "track" in title->list_audio is an index into the source's tracks.
    // "track" in job->list_audio is an index into title->list_audio
    audio->config.in.track = audiocfg->in.track;

    /* Really shouldn't ignore the passed out track, but there is currently no
     * way to handle duplicates or out-of-order track numbers. */
    audio->config.out = audiocfg->out;
    audio->config.out.track = hb_list_count(job->list_audio) + 1;
    if (audiocfg->out.name && *audiocfg->out.name)
    {
        audio->config.out.name = strdup(audiocfg->out.name);
    }

    hb_list_add(job->list_audio, audio);
    return 1;
}