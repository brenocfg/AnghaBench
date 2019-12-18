#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_3__ {int last_scr; scalar_t__ last_pts; int /*<<< orphan*/  scr_changes; } ;
typedef  TYPE_1__ hb_psdemux_t ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 

__attribute__((used)) static inline int check_mpeg_scr( hb_psdemux_t *state, int64_t scr, int tol )
{
    /*
     * This section of code implements the timing model of
     * the "Standard Target Decoder" (STD) of the MPEG2 standard
     * (specified in ISO 13818-1 sections 2.4.2, 2.5.2 & Annex D).
     * The STD removes and corrects for clock discontinuities so
     * that the time stamps on the video, audio & other media
     * streams can be used for cross-media synchronization. To do
     * this the STD has its own timestamp value, the System Clock
     * Reference or SCR, in the PACK header. Clock discontinuities
     * are detected using the SCR & and the adjustment needed
     * to correct post-discontinuity timestamps to be contiguous
     * with pre-discontinuity timestamps is computed from pre- and
     * post-discontinuity values of the SCR. Then this adjustment
     * is applied to every media timestamp (PTS).
     *
     * ISO 13818-1 says there must be an SCR at least every 700ms
     * (100ms for Transport Streams) so if the difference between
     * this SCR & the previous is >700ms it's a discontinuity.
     * If the difference is negative it's non-physical (time doesn't
     * go backward) and must also be a discontinuity. When we find a
     * discontinuity we adjust the scr_offset so that the SCR of the
     * new packet lines up with that of the previous packet.
     */

    // we declare a discontinuity if there's a gap of more than
    // 'tol'ms between the last scr & this or if this scr goes back
    // by more than half a frame time.
    int discontinuity = 0;
    int64_t scr_delta = scr - state->last_scr;
    if (state->last_scr == AV_NOPTS_VALUE ||
        scr_delta > 90*tol || scr_delta < -90*10)
    {
        ++state->scr_changes;
        state->last_pts = AV_NOPTS_VALUE;
        discontinuity = 1;
    }
    state->last_scr = scr;
    return discontinuity;
}