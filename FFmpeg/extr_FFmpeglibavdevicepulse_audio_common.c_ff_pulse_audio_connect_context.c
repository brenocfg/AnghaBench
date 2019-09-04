#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  pa_mainloop_api ;
typedef  int /*<<< orphan*/  pa_mainloop ;
typedef  int /*<<< orphan*/  pa_context ;
typedef  enum PulseAudioContextState { ____Placeholder_PulseAudioContextState } PulseAudioContextState ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int PULSE_CONTEXT_FINISHED ; 
 int PULSE_CONTEXT_INITIALIZING ; 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ff_pulse_audio_disconnect_context (int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 scalar_t__ pa_context_connect (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pa_context_new (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  pa_context_set_state_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * pa_mainloop_get_api (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_mainloop_iterate (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pa_mainloop_new () ; 
 int /*<<< orphan*/  pa_state_cb ; 

int ff_pulse_audio_connect_context(pa_mainloop **pa_ml, pa_context **pa_ctx,
                                   const char *server, const char *description)
{
    int ret;
    pa_mainloop_api *pa_mlapi = NULL;
    enum PulseAudioContextState context_state = PULSE_CONTEXT_INITIALIZING;

    av_assert0(pa_ml);
    av_assert0(pa_ctx);

    *pa_ml = NULL;
    *pa_ctx = NULL;

    if (!(*pa_ml = pa_mainloop_new()))
        return AVERROR(ENOMEM);
    if (!(pa_mlapi = pa_mainloop_get_api(*pa_ml))) {
        ret = AVERROR_EXTERNAL;
        goto fail;
    }
    if (!(*pa_ctx = pa_context_new(pa_mlapi, description))) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }
    pa_context_set_state_callback(*pa_ctx, pa_state_cb, &context_state);
    if (pa_context_connect(*pa_ctx, server, 0, NULL) < 0) {
        ret = AVERROR_EXTERNAL;
        goto fail;
    }

    while (context_state == PULSE_CONTEXT_INITIALIZING)
        pa_mainloop_iterate(*pa_ml, 1, NULL);
    if (context_state == PULSE_CONTEXT_FINISHED) {
        ret = AVERROR_EXTERNAL;
        goto fail;
    }
    return 0;

  fail:
    ff_pulse_audio_disconnect_context(pa_ml, pa_ctx);
    return ret;
}