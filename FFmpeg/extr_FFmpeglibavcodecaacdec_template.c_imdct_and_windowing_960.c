#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  (* imdct_half ) (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ;} ;
struct TYPE_13__ {int /*<<< orphan*/  (* imdct_half ) (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ;} ;
struct TYPE_12__ {TYPE_1__* fdsp; TYPE_5__* mdct960; TYPE_6__* mdct120; int /*<<< orphan*/ * temp; int /*<<< orphan*/ * buf_mdct; } ;
struct TYPE_11__ {scalar_t__* window_sequence; scalar_t__* use_kb_window; } ;
struct TYPE_10__ {int /*<<< orphan*/ * saved; int /*<<< orphan*/ * ret; int /*<<< orphan*/ * coeffs; TYPE_3__ ics; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* vector_fmul_window ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ;} ;
typedef  TYPE_2__ SingleChannelElement ;
typedef  TYPE_3__ IndividualChannelStream ;
typedef  int /*<<< orphan*/  INTFLOAT ;
typedef  TYPE_4__ AACContext ;

/* Variables and functions */
 int /*<<< orphan*/ * AAC_RENAME (int /*<<< orphan*/ ) ; 
 scalar_t__ EIGHT_SHORT_SEQUENCE ; 
 scalar_t__ LONG_START_SEQUENCE ; 
 scalar_t__ LONG_STOP_SEQUENCE ; 
 scalar_t__ ONLY_LONG_SEQUENCE ; 
 int /*<<< orphan*/  ff_aac_kbd_long_960 ; 
 int /*<<< orphan*/  ff_aac_kbd_short_120 ; 
 int /*<<< orphan*/  ff_sine_120 ; 
 int /*<<< orphan*/  ff_sine_960 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stub11 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stub12 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void imdct_and_windowing_960(AACContext *ac, SingleChannelElement *sce)
{
#if !USE_FIXED
    IndividualChannelStream *ics = &sce->ics;
    INTFLOAT *in    = sce->coeffs;
    INTFLOAT *out   = sce->ret;
    INTFLOAT *saved = sce->saved;
    const INTFLOAT *swindow      = ics->use_kb_window[0] ? AAC_RENAME(ff_aac_kbd_short_120) : AAC_RENAME(ff_sine_120);
    const INTFLOAT *lwindow_prev = ics->use_kb_window[1] ? AAC_RENAME(ff_aac_kbd_long_960) : AAC_RENAME(ff_sine_960);
    const INTFLOAT *swindow_prev = ics->use_kb_window[1] ? AAC_RENAME(ff_aac_kbd_short_120) : AAC_RENAME(ff_sine_120);
    INTFLOAT *buf  = ac->buf_mdct;
    INTFLOAT *temp = ac->temp;
    int i;

    // imdct
    if (ics->window_sequence[0] == EIGHT_SHORT_SEQUENCE) {
        for (i = 0; i < 8; i++)
            ac->mdct120->imdct_half(ac->mdct120, buf + i * 120, in + i * 128, 1);
    } else {
        ac->mdct960->imdct_half(ac->mdct960, buf, in, 1);
    }

    /* window overlapping
     * NOTE: To simplify the overlapping code, all 'meaningless' short to long
     * and long to short transitions are considered to be short to short
     * transitions. This leaves just two cases (long to long and short to short)
     * with a little special sauce for EIGHT_SHORT_SEQUENCE.
     */

    if ((ics->window_sequence[1] == ONLY_LONG_SEQUENCE || ics->window_sequence[1] == LONG_STOP_SEQUENCE) &&
        (ics->window_sequence[0] == ONLY_LONG_SEQUENCE || ics->window_sequence[0] == LONG_START_SEQUENCE)) {
        ac->fdsp->vector_fmul_window(    out,               saved,            buf,         lwindow_prev, 480);
    } else {
        memcpy(                          out,               saved,            420 * sizeof(*out));

        if (ics->window_sequence[0] == EIGHT_SHORT_SEQUENCE) {
            ac->fdsp->vector_fmul_window(out + 420 + 0*120, saved + 420,      buf + 0*120, swindow_prev, 60);
            ac->fdsp->vector_fmul_window(out + 420 + 1*120, buf + 0*120 + 60, buf + 1*120, swindow,      60);
            ac->fdsp->vector_fmul_window(out + 420 + 2*120, buf + 1*120 + 60, buf + 2*120, swindow,      60);
            ac->fdsp->vector_fmul_window(out + 420 + 3*120, buf + 2*120 + 60, buf + 3*120, swindow,      60);
            ac->fdsp->vector_fmul_window(temp,              buf + 3*120 + 60, buf + 4*120, swindow,      60);
            memcpy(                      out + 420 + 4*120, temp, 60 * sizeof(*out));
        } else {
            ac->fdsp->vector_fmul_window(out + 420,         saved + 420,      buf,         swindow_prev, 60);
            memcpy(                      out + 540,         buf + 60,         420 * sizeof(*out));
        }
    }

    // buffer update
    if (ics->window_sequence[0] == EIGHT_SHORT_SEQUENCE) {
        memcpy(                      saved,       temp + 60,         60 * sizeof(*saved));
        ac->fdsp->vector_fmul_window(saved + 60,  buf + 4*120 + 60, buf + 5*120, swindow, 60);
        ac->fdsp->vector_fmul_window(saved + 180, buf + 5*120 + 60, buf + 6*120, swindow, 60);
        ac->fdsp->vector_fmul_window(saved + 300, buf + 6*120 + 60, buf + 7*120, swindow, 60);
        memcpy(                      saved + 420, buf + 7*120 + 60,  60 * sizeof(*saved));
    } else if (ics->window_sequence[0] == LONG_START_SEQUENCE) {
        memcpy(                      saved,       buf + 480,        420 * sizeof(*saved));
        memcpy(                      saved + 420, buf + 7*120 + 60,  60 * sizeof(*saved));
    } else { // LONG_STOP or ONLY_LONG
        memcpy(                      saved,       buf + 480,        480 * sizeof(*saved));
    }
#endif
}