#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int offset; int freq; int mode; int amplitude; int phase; } ;
struct TYPE_4__ {int* nb_tones; TYPE_3__** tones; int /*<<< orphan*/  avctx; } ;
typedef  TYPE_1__ QDMCContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int const FF_ARRAY_ELEMS (TYPE_3__*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void add_tone(QDMCContext *s, int group, int offset, int freq, int stereo_mode, int amplitude, int phase)
{
    const int index = s->nb_tones[group];

    if (index >= FF_ARRAY_ELEMS(s->tones[group])) {
        av_log(s->avctx, AV_LOG_WARNING, "Too many tones already in buffer, ignoring tone!\n");
        return;
    }

    s->tones[group][index].offset    = offset;
    s->tones[group][index].freq      = freq;
    s->tones[group][index].mode      = stereo_mode;
    s->tones[group][index].amplitude = amplitude;
    s->tones[group][index].phase     = phase;
    s->nb_tones[group]++;
}