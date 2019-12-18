#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* noise_buf; } ;
struct TYPE_5__ {int channels; TYPE_4__* state; int /*<<< orphan*/  ac_out; int /*<<< orphan*/  ac_in; int /*<<< orphan*/  s16_data; int /*<<< orphan*/  flt_data; } ;
typedef  TYPE_1__ DitherContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (TYPE_4__*) ; 
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 
 int /*<<< orphan*/  ff_audio_convert_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_audio_data_free (int /*<<< orphan*/ *) ; 

void ff_dither_free(DitherContext **cp)
{
    DitherContext *c = *cp;
    int ch;

    if (!c)
        return;
    ff_audio_data_free(&c->flt_data);
    ff_audio_data_free(&c->s16_data);
    ff_audio_convert_free(&c->ac_in);
    ff_audio_convert_free(&c->ac_out);
    for (ch = 0; ch < c->channels; ch++)
        av_free(c->state[ch].noise_buf);
    av_free(c->state);
    av_freep(cp);
}