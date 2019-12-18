#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  enum Mode { ____Placeholder_Mode } Mode ;
struct TYPE_6__ {int /*<<< orphan*/  (* acelp_interpolatef ) (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int,int,int) ;} ;
struct TYPE_8__ {int cur_frame_mode; int pitch_lag_int; scalar_t__ excitation; int /*<<< orphan*/  pitch_vector; TYPE_1__ acelpf_ctx; } ;
struct TYPE_7__ {int /*<<< orphan*/  p_lag; } ;
typedef  TYPE_2__ AMRNBSubframe ;
typedef  TYPE_3__ AMRContext ;

/* Variables and functions */
 int AMR_SUBFRAME_SIZE ; 
 scalar_t__ MODE_12k2 ; 
 int MODE_4k75 ; 
 int MODE_5k15 ; 
 int MODE_6k7 ; 
 int MODE_7k95 ; 
 int /*<<< orphan*/  decode_pitch_lag_1_6 (int*,int*,int /*<<< orphan*/ ,int,int const) ; 
 int /*<<< orphan*/  ff_b60_sinc ; 
 int /*<<< orphan*/  ff_decode_pitch_lag (int*,int*,int /*<<< orphan*/ ,int,int const,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static void decode_pitch_vector(AMRContext *p,
                                const AMRNBSubframe *amr_subframe,
                                const int subframe)
{
    int pitch_lag_int, pitch_lag_frac;
    enum Mode mode = p->cur_frame_mode;

    if (p->cur_frame_mode == MODE_12k2) {
        decode_pitch_lag_1_6(&pitch_lag_int, &pitch_lag_frac,
                             amr_subframe->p_lag, p->pitch_lag_int,
                             subframe);
    } else {
        ff_decode_pitch_lag(&pitch_lag_int, &pitch_lag_frac,
                            amr_subframe->p_lag,
                            p->pitch_lag_int, subframe,
                            mode != MODE_4k75 && mode != MODE_5k15,
                            mode <= MODE_6k7 ? 4 : (mode == MODE_7k95 ? 5 : 6));
        pitch_lag_frac *= 2;
    }

    p->pitch_lag_int = pitch_lag_int; // store previous lag in a uint8_t

    pitch_lag_int += pitch_lag_frac > 0;

    /* Calculate the pitch vector by interpolating the past excitation at the
       pitch lag using a b60 hamming windowed sinc function.   */
    p->acelpf_ctx.acelp_interpolatef(p->excitation,
                          p->excitation + 1 - pitch_lag_int,
                          ff_b60_sinc, 6,
                          pitch_lag_frac + 6 - 6*(pitch_lag_frac > 0),
                          10, AMR_SUBFRAME_SIZE);

    memcpy(p->pitch_vector, p->excitation, AMR_SUBFRAME_SIZE * sizeof(float));
}