#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_11__ {int utt_started; int /*<<< orphan*/  ps; } ;
struct TYPE_10__ {int /*<<< orphan*/ * outputs; TYPE_4__* priv; } ;
struct TYPE_9__ {TYPE_3__* dst; } ;
struct TYPE_8__ {int /*<<< orphan*/  nb_samples; scalar_t__* data; int /*<<< orphan*/ * metadata; } ;
typedef  TYPE_1__ AVFrame ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;
typedef  int /*<<< orphan*/  AVDictionary ;
typedef  TYPE_4__ ASRContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,char*,char const*,int /*<<< orphan*/ ) ; 
 int ff_filter_frame (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ps_end_utt (int /*<<< orphan*/ ) ; 
 char* ps_get_hyp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ps_get_in_speech (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps_process_raw (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps_start_utt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int filter_frame(AVFilterLink *inlink, AVFrame *in)
{
    AVFilterContext *ctx = inlink->dst;
    AVDictionary **metadata = &in->metadata;
    ASRContext *s = ctx->priv;
    int have_speech;
    const char *speech;

    ps_process_raw(s->ps, (const int16_t *)in->data[0], in->nb_samples, 0, 0);
    have_speech = ps_get_in_speech(s->ps);
    if (have_speech && !s->utt_started)
        s->utt_started = 1;
    if (!have_speech && s->utt_started) {
        ps_end_utt(s->ps);
        speech = ps_get_hyp(s->ps, NULL);
        if (speech != NULL)
            av_dict_set(metadata, "lavfi.asr.text", speech, 0);
        ps_start_utt(s->ps);
        s->utt_started = 0;
    }

    return ff_filter_frame(ctx->outputs[0], in);
}