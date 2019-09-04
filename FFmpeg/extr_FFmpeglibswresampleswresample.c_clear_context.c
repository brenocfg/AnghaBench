#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  temp; int /*<<< orphan*/  noise; } ;
struct TYPE_8__ {int /*<<< orphan*/  ch; } ;
struct TYPE_7__ {int /*<<< orphan*/  ch; } ;
struct TYPE_10__ {scalar_t__ flushed; scalar_t__ delayed_samples_fixup; int /*<<< orphan*/  full_convert; int /*<<< orphan*/  out_convert; int /*<<< orphan*/  in_convert; TYPE_3__ dither; int /*<<< orphan*/  drop_temp; int /*<<< orphan*/  silence; int /*<<< orphan*/  in_buffer; int /*<<< orphan*/  preout; int /*<<< orphan*/  midbuf; int /*<<< orphan*/  postin; TYPE_2__ out; TYPE_1__ in; scalar_t__ resample_in_constraint; scalar_t__ in_buffer_count; scalar_t__ in_buffer_index; } ;
typedef  TYPE_4__ SwrContext ;

/* Variables and functions */
 int /*<<< orphan*/  free_temp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  swri_audio_convert_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swri_rematrix_free (TYPE_4__*) ; 

__attribute__((used)) static void clear_context(SwrContext *s){
    s->in_buffer_index= 0;
    s->in_buffer_count= 0;
    s->resample_in_constraint= 0;
    memset(s->in.ch, 0, sizeof(s->in.ch));
    memset(s->out.ch, 0, sizeof(s->out.ch));
    free_temp(&s->postin);
    free_temp(&s->midbuf);
    free_temp(&s->preout);
    free_temp(&s->in_buffer);
    free_temp(&s->silence);
    free_temp(&s->drop_temp);
    free_temp(&s->dither.noise);
    free_temp(&s->dither.temp);
    swri_audio_convert_free(&s-> in_convert);
    swri_audio_convert_free(&s->out_convert);
    swri_audio_convert_free(&s->full_convert);
    swri_rematrix_free(s);

    s->delayed_samples_fixup = 0;
    s->flushed = 0;
}