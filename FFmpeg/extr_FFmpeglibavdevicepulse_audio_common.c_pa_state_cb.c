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
typedef  int /*<<< orphan*/  pa_context ;
typedef  enum PulseAudioContextState { ____Placeholder_PulseAudioContextState } PulseAudioContextState ;

/* Variables and functions */
#define  PA_CONTEXT_FAILED 130 
#define  PA_CONTEXT_READY 129 
#define  PA_CONTEXT_TERMINATED 128 
 int PULSE_CONTEXT_FINISHED ; 
 int PULSE_CONTEXT_READY ; 
 int pa_context_get_state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pa_state_cb(pa_context *c, void *userdata)
{
    enum PulseAudioContextState *context_state = userdata;

    switch  (pa_context_get_state(c)) {
    case PA_CONTEXT_FAILED:
    case PA_CONTEXT_TERMINATED:
        *context_state = PULSE_CONTEXT_FINISHED;
        break;
    case PA_CONTEXT_READY:
        *context_state = PULSE_CONTEXT_READY;
        break;
    default:
        break;
    }
}