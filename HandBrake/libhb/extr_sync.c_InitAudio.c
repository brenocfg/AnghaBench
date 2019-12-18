#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_11__ ;

/* Type definitions */
struct TYPE_26__ {int /*<<< orphan*/  list_work; TYPE_7__* streams; TYPE_1__* job; } ;
typedef  TYPE_8__ sync_common_t ;
typedef  void* int64_t ;
struct TYPE_27__ {TYPE_7__* stream; int /*<<< orphan*/  fifo_out; TYPE_8__* common; int /*<<< orphan*/ * fifo_in; TYPE_11__* audio; struct TYPE_27__* private_data; } ;
typedef  TYPE_9__ hb_work_private_t ;
typedef  TYPE_9__ hb_work_object_t ;
struct TYPE_22__ {int codec; scalar_t__ samplerate; int gain; int /*<<< orphan*/  normalize_mix_level; int /*<<< orphan*/  mixdown; } ;
struct TYPE_21__ {scalar_t__ samplerate; } ;
struct TYPE_23__ {TYPE_4__ out; TYPE_3__ in; } ;
struct TYPE_20__ {int /*<<< orphan*/  fifo_sync; int /*<<< orphan*/  fifo_out; int /*<<< orphan*/ * fifo_raw; } ;
struct TYPE_18__ {TYPE_5__ config; int /*<<< orphan*/  id; TYPE_2__ priv; } ;
typedef  TYPE_11__ hb_audio_t ;
struct TYPE_24__ {int /*<<< orphan*/ * resample; int /*<<< orphan*/  gain_factor; TYPE_11__* audio; } ;
struct TYPE_25__ {int last_scr_sequence; int /*<<< orphan*/ * in_queue; int /*<<< orphan*/ * delta_list; TYPE_6__ audio; int /*<<< orphan*/  fifo_out; void* last_duration; void* last_scr_pts; void* last_pts; void* next_pts; scalar_t__ first_pts; int /*<<< orphan*/  type; int /*<<< orphan*/  min_len; int /*<<< orphan*/  max_len; void* scr_delay_queue; TYPE_8__* common; } ;
struct TYPE_19__ {int /*<<< orphan*/  h; int /*<<< orphan*/  list_audio; } ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_FLT ; 
 int HB_ACODEC_PASS_FLAG ; 
 int /*<<< orphan*/  SYNC_MAX_AUDIO_QUEUE_LEN ; 
 int /*<<< orphan*/  SYNC_MIN_AUDIO_QUEUE_LEN ; 
 int /*<<< orphan*/  SYNC_TYPE_AUDIO ; 
 int /*<<< orphan*/  WORK_SYNC_AUDIO ; 
 TYPE_9__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_9__*) ; 
 int /*<<< orphan*/  hb_audio_resample_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_audio_resample_init (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_audio_resample_set_sample_rate (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ hb_audio_resample_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_error (char*,int /*<<< orphan*/ ) ; 
 TYPE_9__* hb_get_work (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_list_add (int /*<<< orphan*/ ,TYPE_9__*) ; 
 int /*<<< orphan*/  hb_list_close (int /*<<< orphan*/ **) ; 
 void* hb_list_init () ; 
 TYPE_11__* hb_list_item (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pow (int,int) ; 

__attribute__((used)) static int InitAudio( sync_common_t * common, int index )
{
    hb_work_object_t  * w = NULL;
    hb_work_private_t * pv;
    hb_audio_t        * audio;

    audio = hb_list_item(common->job->list_audio, index);
    if (audio->priv.fifo_raw == NULL)
    {
        // No input fifo, not configured
        return 0;
    }
    pv = calloc(1, sizeof(hb_work_private_t));
    if (pv == NULL) goto fail;

    w = hb_get_work(common->job->h, WORK_SYNC_AUDIO);
    w->private_data = pv;
    w->audio        = audio;
    w->fifo_in      = audio->priv.fifo_raw;
    if (audio->config.out.codec & HB_ACODEC_PASS_FLAG)
    {
        w->fifo_out = audio->priv.fifo_out;
    }
    else
    {
        w->fifo_out = audio->priv.fifo_sync;
    }

    pv->common                  = common;
    pv->stream                  = &common->streams[1 + index];
    pv->stream->common          = common;
    pv->stream->in_queue        = hb_list_init();
    pv->stream->scr_delay_queue = hb_list_init();
    pv->stream->max_len         = SYNC_MAX_AUDIO_QUEUE_LEN;
    pv->stream->min_len         = SYNC_MIN_AUDIO_QUEUE_LEN;
    if (pv->stream->in_queue == NULL) goto fail;
    pv->stream->delta_list      = hb_list_init();
    if (pv->stream->delta_list == NULL) goto fail;
    pv->stream->type            = SYNC_TYPE_AUDIO;
    pv->stream->first_pts       = AV_NOPTS_VALUE;
    pv->stream->next_pts        = (int64_t)AV_NOPTS_VALUE;
    pv->stream->last_pts        = (int64_t)AV_NOPTS_VALUE;
    pv->stream->last_scr_pts    = (int64_t)AV_NOPTS_VALUE;
    pv->stream->last_scr_sequence = -1;
    pv->stream->last_duration   = (int64_t)AV_NOPTS_VALUE;
    pv->stream->audio.audio     = audio;
    pv->stream->fifo_out        = w->fifo_out;

    if (!(audio->config.out.codec & HB_ACODEC_PASS_FLAG) &&
        audio->config.in.samplerate != audio->config.out.samplerate)
    {
        /* Initialize samplerate conversion */
        pv->stream->audio.resample =
            hb_audio_resample_init(AV_SAMPLE_FMT_FLT,
                                   audio->config.out.samplerate,
                                   audio->config.out.mixdown,
                                   audio->config.out.normalize_mix_level);
        if (pv->stream->audio.resample == NULL)
        {
            hb_error("sync: audio 0x%x resample init failed", audio->id);
            goto fail;
        }
        hb_audio_resample_set_sample_rate(pv->stream->audio.resample,
                                          audio->config.in.samplerate);
        if (hb_audio_resample_update(pv->stream->audio.resample))
        {
            hb_error("sync: audio 0x%x resample update failed", audio->id);
            goto fail;
        }
    }

    pv->stream->audio.gain_factor = pow(10, audio->config.out.gain / 20);

    hb_list_add(common->list_work, w);

    return 0;

fail:
    if (pv != NULL)
    {
        if (pv->stream != NULL)
        {
            if (pv->stream->audio.resample)
            {
                hb_audio_resample_free(pv->stream->audio.resample);
            }
            hb_list_close(&pv->stream->delta_list);
            hb_list_close(&pv->stream->in_queue);
        }
    }
    free(pv);
    free(w);

    return 1;
}