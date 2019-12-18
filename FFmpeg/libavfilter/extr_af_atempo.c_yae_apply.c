#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_12__ {int /*<<< orphan*/  xdat; } ;
struct TYPE_11__ {scalar_t__ state; int /*<<< orphan*/  real_to_complex; int /*<<< orphan*/  nfrag; } ;
typedef  TYPE_1__ ATempoContext ;

/* Variables and functions */
 scalar_t__ YAE_ADJUST_POSITION ; 
 scalar_t__ YAE_LOAD_FRAGMENT ; 
 scalar_t__ YAE_OUTPUT_OVERLAP_ADD ; 
 scalar_t__ YAE_RELOAD_FRAGMENT ; 
 int /*<<< orphan*/  av_rdft_calc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ yae_adjust_position (TYPE_1__*) ; 
 int /*<<< orphan*/  yae_advance_to_next_frag (TYPE_1__*) ; 
 TYPE_5__* yae_curr_frag (TYPE_1__*) ; 
 int /*<<< orphan*/  yae_downmix (TYPE_1__*,TYPE_5__*) ; 
 scalar_t__ yae_load_frag (TYPE_1__*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*) ; 
 scalar_t__ yae_overlap_add (TYPE_1__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
yae_apply(ATempoContext *atempo,
          const uint8_t **src_ref,
          const uint8_t *src_end,
          uint8_t **dst_ref,
          uint8_t *dst_end)
{
    while (1) {
        if (atempo->state == YAE_LOAD_FRAGMENT) {
            // load additional data for the current fragment:
            if (yae_load_frag(atempo, src_ref, src_end) != 0) {
                break;
            }

            // down-mix to mono:
            yae_downmix(atempo, yae_curr_frag(atempo));

            // apply rDFT:
            av_rdft_calc(atempo->real_to_complex, yae_curr_frag(atempo)->xdat);

            // must load the second fragment before alignment can start:
            if (!atempo->nfrag) {
                yae_advance_to_next_frag(atempo);
                continue;
            }

            atempo->state = YAE_ADJUST_POSITION;
        }

        if (atempo->state == YAE_ADJUST_POSITION) {
            // adjust position for better alignment:
            if (yae_adjust_position(atempo)) {
                // reload the fragment at the corrected position, so that the
                // Hann window blending would not require normalization:
                atempo->state = YAE_RELOAD_FRAGMENT;
            } else {
                atempo->state = YAE_OUTPUT_OVERLAP_ADD;
            }
        }

        if (atempo->state == YAE_RELOAD_FRAGMENT) {
            // load additional data if necessary due to position adjustment:
            if (yae_load_frag(atempo, src_ref, src_end) != 0) {
                break;
            }

            // down-mix to mono:
            yae_downmix(atempo, yae_curr_frag(atempo));

            // apply rDFT:
            av_rdft_calc(atempo->real_to_complex, yae_curr_frag(atempo)->xdat);

            atempo->state = YAE_OUTPUT_OVERLAP_ADD;
        }

        if (atempo->state == YAE_OUTPUT_OVERLAP_ADD) {
            // overlap-add and output the result:
            if (yae_overlap_add(atempo, dst_ref, dst_end) != 0) {
                break;
            }

            // advance to the next fragment, repeat:
            yae_advance_to_next_frag(atempo);
            atempo->state = YAE_LOAD_FRAGMENT;
        }
    }
}