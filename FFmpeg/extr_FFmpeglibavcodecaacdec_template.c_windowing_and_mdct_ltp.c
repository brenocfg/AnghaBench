#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  (* mdct_calc ) (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_9__ {TYPE_6__ mdct_ltp; TYPE_1__* fdsp; } ;
struct TYPE_8__ {scalar_t__* window_sequence; scalar_t__* use_kb_window; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* vector_fmul_reverse ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ;int /*<<< orphan*/  (* vector_fmul ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ;} ;
typedef  TYPE_2__ IndividualChannelStream ;
typedef  int /*<<< orphan*/  INTFLOAT ;
typedef  TYPE_3__ AACContext ;

/* Variables and functions */
 int /*<<< orphan*/ * AAC_RENAME (int /*<<< orphan*/ ) ; 
 scalar_t__ LONG_START_SEQUENCE ; 
 scalar_t__ LONG_STOP_SEQUENCE ; 
 int /*<<< orphan*/  ff_aac_kbd_long_1024 ; 
 int /*<<< orphan*/  ff_aac_kbd_short_128 ; 
 int /*<<< orphan*/  ff_sine_1024 ; 
 int /*<<< orphan*/  ff_sine_128 ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stub5 (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void windowing_and_mdct_ltp(AACContext *ac, INTFLOAT *out,
                                   INTFLOAT *in, IndividualChannelStream *ics)
{
    const INTFLOAT *lwindow      = ics->use_kb_window[0] ? AAC_RENAME(ff_aac_kbd_long_1024) : AAC_RENAME(ff_sine_1024);
    const INTFLOAT *swindow      = ics->use_kb_window[0] ? AAC_RENAME(ff_aac_kbd_short_128) : AAC_RENAME(ff_sine_128);
    const INTFLOAT *lwindow_prev = ics->use_kb_window[1] ? AAC_RENAME(ff_aac_kbd_long_1024) : AAC_RENAME(ff_sine_1024);
    const INTFLOAT *swindow_prev = ics->use_kb_window[1] ? AAC_RENAME(ff_aac_kbd_short_128) : AAC_RENAME(ff_sine_128);

    if (ics->window_sequence[0] != LONG_STOP_SEQUENCE) {
        ac->fdsp->vector_fmul(in, in, lwindow_prev, 1024);
    } else {
        memset(in, 0, 448 * sizeof(*in));
        ac->fdsp->vector_fmul(in + 448, in + 448, swindow_prev, 128);
    }
    if (ics->window_sequence[0] != LONG_START_SEQUENCE) {
        ac->fdsp->vector_fmul_reverse(in + 1024, in + 1024, lwindow, 1024);
    } else {
        ac->fdsp->vector_fmul_reverse(in + 1024 + 448, in + 1024 + 448, swindow, 128);
        memset(in + 1024 + 576, 0, 448 * sizeof(*in));
    }
    ac->mdct_ltp.mdct_calc(&ac->mdct_ltp, out, in);
}