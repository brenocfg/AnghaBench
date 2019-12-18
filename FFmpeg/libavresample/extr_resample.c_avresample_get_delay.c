#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* resample; int /*<<< orphan*/  resample_needed; } ;
struct TYPE_6__ {scalar_t__ padding_size; TYPE_1__* buffer; } ;
struct TYPE_5__ {scalar_t__ nb_samples; } ;
typedef  TYPE_2__ ResampleContext ;
typedef  TYPE_3__ AVAudioResampleContext ;

/* Variables and functions */
 int FFMAX (scalar_t__,int /*<<< orphan*/ ) ; 

int avresample_get_delay(AVAudioResampleContext *avr)
{
    ResampleContext *c = avr->resample;

    if (!avr->resample_needed || !avr->resample)
        return 0;

    return FFMAX(c->buffer->nb_samples - c->padding_size, 0);
}