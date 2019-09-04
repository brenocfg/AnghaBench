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
typedef  int /*<<< orphan*/  pa_mainloop ;
typedef  int /*<<< orphan*/  pa_context ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pa_context_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_context_set_state_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_context_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pa_mainloop_free (int /*<<< orphan*/ *) ; 

void ff_pulse_audio_disconnect_context(pa_mainloop **pa_ml, pa_context **pa_ctx)
{
    av_assert0(pa_ml);
    av_assert0(pa_ctx);

    if (*pa_ctx) {
        pa_context_set_state_callback(*pa_ctx, NULL, NULL);
        pa_context_disconnect(*pa_ctx);
        pa_context_unref(*pa_ctx);
    }
    if (*pa_ml)
        pa_mainloop_free(*pa_ml);
    *pa_ml = NULL;
    *pa_ctx = NULL;
}