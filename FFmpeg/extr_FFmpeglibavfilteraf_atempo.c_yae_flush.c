#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_13__ {scalar_t__* position; int window; scalar_t__ stride; int /*<<< orphan*/  real_to_complex; scalar_t__ nfrag; int /*<<< orphan*/  state; } ;
struct TYPE_12__ {scalar_t__* position; scalar_t__ nsamples; int /*<<< orphan*/ * data; int /*<<< orphan*/  xdat; } ;
typedef  TYPE_1__ AudioFragment ;
typedef  TYPE_2__ ATempoContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EAGAIN ; 
 scalar_t__ FFMAX (scalar_t__,scalar_t__) ; 
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  YAE_FLUSH_OUTPUT ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_rdft_calc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ yae_adjust_position (TYPE_2__*) ; 
 int /*<<< orphan*/  yae_advance_to_next_frag (TYPE_2__*) ; 
 TYPE_1__* yae_curr_frag (TYPE_2__*) ; 
 int /*<<< orphan*/  yae_downmix (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  yae_load_frag (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ yae_overlap_add (TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int yae_flush(ATempoContext *atempo,
                     uint8_t **dst_ref,
                     uint8_t *dst_end)
{
    AudioFragment *frag = yae_curr_frag(atempo);
    int64_t overlap_end;
    int64_t start_here;
    int64_t stop_here;
    int64_t offset;

    const uint8_t *src;
    uint8_t *dst;

    int src_size;
    int dst_size;
    int nbytes;

    atempo->state = YAE_FLUSH_OUTPUT;

    if (!atempo->nfrag) {
        // there is nothing to flush:
        return 0;
    }

    if (atempo->position[0] == frag->position[0] + frag->nsamples &&
        atempo->position[1] == frag->position[1] + frag->nsamples) {
        // the current fragment is already flushed:
        return 0;
    }

    if (frag->position[0] + frag->nsamples < atempo->position[0]) {
        // finish loading the current (possibly partial) fragment:
        yae_load_frag(atempo, NULL, NULL);

        if (atempo->nfrag) {
            // down-mix to mono:
            yae_downmix(atempo, frag);

            // apply rDFT:
            av_rdft_calc(atempo->real_to_complex, frag->xdat);

            // align current fragment to previous fragment:
            if (yae_adjust_position(atempo)) {
                // reload the current fragment due to adjusted position:
                yae_load_frag(atempo, NULL, NULL);
            }
        }
    }

    // flush the overlap region:
    overlap_end = frag->position[1] + FFMIN(atempo->window / 2,
                                            frag->nsamples);

    while (atempo->position[1] < overlap_end) {
        if (yae_overlap_add(atempo, dst_ref, dst_end) != 0) {
            return AVERROR(EAGAIN);
        }
    }

    // check whether all of the input samples have been consumed:
    if (frag->position[0] + frag->nsamples < atempo->position[0]) {
        yae_advance_to_next_frag(atempo);
        return AVERROR(EAGAIN);
    }

    // flush the remainder of the current fragment:
    start_here = FFMAX(atempo->position[1], overlap_end);
    stop_here  = frag->position[1] + frag->nsamples;
    offset     = start_here - frag->position[1];
    av_assert0(start_here <= stop_here && frag->position[1] <= start_here);

    src = frag->data + offset * atempo->stride;
    dst = (uint8_t *)*dst_ref;

    src_size = (int)(stop_here - start_here) * atempo->stride;
    dst_size = dst_end - dst;
    nbytes = FFMIN(src_size, dst_size);

    memcpy(dst, src, nbytes);
    dst += nbytes;

    atempo->position[1] += (nbytes / atempo->stride);

    // pass-back the updated destination buffer pointer:
    *dst_ref = (uint8_t *)dst;

    return atempo->position[1] == stop_here ? 0 : AVERROR(EAGAIN);
}