#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_13__ {int /*<<< orphan*/ * resample; scalar_t__ next_pts; int /*<<< orphan*/ * job; } ;
typedef  TYPE_5__ hb_work_private_t ;
struct TYPE_14__ {TYPE_4__* audio; TYPE_5__* private_data; } ;
typedef  TYPE_6__ hb_work_object_t ;
typedef  int /*<<< orphan*/  hb_job_t ;
struct TYPE_10__ {int /*<<< orphan*/  normalize_mix_level; int /*<<< orphan*/  mixdown; } ;
struct TYPE_9__ {int /*<<< orphan*/  samplerate; } ;
struct TYPE_11__ {TYPE_2__ out; TYPE_1__ in; } ;
struct TYPE_12__ {TYPE_3__ config; } ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_FLT ; 
 TYPE_5__* calloc (int,int) ; 
 int /*<<< orphan*/ * hb_audio_resample_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_error (char*) ; 

__attribute__((used)) static int declpcmInit( hb_work_object_t * w, hb_job_t * job )
{
    hb_work_private_t * pv = calloc( 1, sizeof( hb_work_private_t ) );
    w->private_data = pv;
    pv->job = job;

    pv->next_pts = (int64_t)AV_NOPTS_VALUE;
    // Currently, samplerate conversion is performed in sync.c
    // So set output samplerate to input samplerate
    // This should someday get reworked to be part of an audio filter pipleine.
    pv->resample =
        hb_audio_resample_init(AV_SAMPLE_FMT_FLT,
                               w->audio->config.in.samplerate,
                               w->audio->config.out.mixdown,
                               w->audio->config.out.normalize_mix_level);
    if (pv->resample == NULL)
    {
        hb_error("declpcmInit: hb_audio_resample_init() failed");
        return 1;
    }

    return 0;
}