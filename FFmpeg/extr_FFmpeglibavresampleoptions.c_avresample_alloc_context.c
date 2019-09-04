#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * av_class; } ;
typedef  TYPE_1__ AVAudioResampleContext ;

/* Variables and functions */
 TYPE_1__* av_mallocz (int) ; 
 int /*<<< orphan*/  av_opt_set_defaults (TYPE_1__*) ; 
 int /*<<< orphan*/  av_resample_context_class ; 

AVAudioResampleContext *avresample_alloc_context(void)
{
    AVAudioResampleContext *avr;

    avr = av_mallocz(sizeof(*avr));
    if (!avr)
        return NULL;

    avr->av_class = &av_resample_context_class;
    av_opt_set_defaults(avr);

    return avr;
}