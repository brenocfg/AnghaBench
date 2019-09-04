#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  matrix_flt; int /*<<< orphan*/  matrix_q15; int /*<<< orphan*/  matrix_q8; int /*<<< orphan*/ * matrix; } ;
typedef  TYPE_1__ AudioMix ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void ff_audio_mix_free(AudioMix **am_p)
{
    AudioMix *am;

    if (!*am_p)
        return;
    am = *am_p;

    if (am->matrix) {
        av_free(am->matrix[0]);
        am->matrix = NULL;
    }
    memset(am->matrix_q8,  0, sizeof(am->matrix_q8 ));
    memset(am->matrix_q15, 0, sizeof(am->matrix_q15));
    memset(am->matrix_flt, 0, sizeof(am->matrix_flt));

    av_freep(am_p);
}