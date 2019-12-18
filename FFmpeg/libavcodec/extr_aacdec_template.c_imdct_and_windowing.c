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
struct TYPE_14__ {int /*<<< orphan*/  (* imdct_half ) (TYPE_6__*,long long*,long long*) ;} ;
struct TYPE_13__ {int /*<<< orphan*/  (* imdct_half ) (TYPE_5__*,long long*,long long*) ;} ;
struct TYPE_12__ {long long* buf_mdct; long long* temp; TYPE_1__* fdsp; TYPE_5__ mdct; TYPE_6__ mdct_small; } ;
struct TYPE_11__ {scalar_t__* window_sequence; scalar_t__* use_kb_window; } ;
struct TYPE_10__ {long long* coeffs; long long* ret; long long* saved; TYPE_3__ ics; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* vector_fmul_window ) (long long*,long long*,long long*,long long const*,int) ;} ;
typedef  TYPE_2__ SingleChannelElement ;
typedef  TYPE_3__ IndividualChannelStream ;
typedef  long long INTFLOAT ;
typedef  TYPE_4__ AACContext ;

/* Variables and functions */
 long long* AAC_RENAME (int /*<<< orphan*/ ) ; 
 scalar_t__ EIGHT_SHORT_SEQUENCE ; 
 scalar_t__ LONG_START_SEQUENCE ; 
 scalar_t__ LONG_STOP_SEQUENCE ; 
 scalar_t__ ONLY_LONG_SEQUENCE ; 
 int /*<<< orphan*/  ff_aac_kbd_long_1024 ; 
 int /*<<< orphan*/  ff_aac_kbd_short_128 ; 
 int /*<<< orphan*/  ff_sine_1024 ; 
 int /*<<< orphan*/  ff_sine_128 ; 
 int /*<<< orphan*/  memcpy (long long*,long long*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,long long*,long long*) ; 
 int /*<<< orphan*/  stub10 (long long*,long long*,long long*,long long const*,int) ; 
 int /*<<< orphan*/  stub11 (long long*,long long*,long long*,long long const*,int) ; 
 int /*<<< orphan*/  stub12 (long long*,long long*,long long*,long long const*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,long long*,long long*) ; 
 int /*<<< orphan*/  stub3 (long long*,long long*,long long*,long long const*,int) ; 
 int /*<<< orphan*/  stub4 (long long*,long long*,long long*,long long const*,int) ; 
 int /*<<< orphan*/  stub5 (long long*,long long*,long long*,long long const*,int) ; 
 int /*<<< orphan*/  stub6 (long long*,long long*,long long*,long long const*,int) ; 
 int /*<<< orphan*/  stub7 (long long*,long long*,long long*,long long const*,int) ; 
 int /*<<< orphan*/  stub8 (long long*,long long*,long long*,long long const*,int) ; 
 int /*<<< orphan*/  stub9 (long long*,long long*,long long*,long long const*,int) ; 

__attribute__((used)) static void imdct_and_windowing(AACContext *ac, SingleChannelElement *sce)
{
    IndividualChannelStream *ics = &sce->ics;
    INTFLOAT *in    = sce->coeffs;
    INTFLOAT *out   = sce->ret;
    INTFLOAT *saved = sce->saved;
    const INTFLOAT *swindow      = ics->use_kb_window[0] ? AAC_RENAME(ff_aac_kbd_short_128) : AAC_RENAME(ff_sine_128);
    const INTFLOAT *lwindow_prev = ics->use_kb_window[1] ? AAC_RENAME(ff_aac_kbd_long_1024) : AAC_RENAME(ff_sine_1024);
    const INTFLOAT *swindow_prev = ics->use_kb_window[1] ? AAC_RENAME(ff_aac_kbd_short_128) : AAC_RENAME(ff_sine_128);
    INTFLOAT *buf  = ac->buf_mdct;
    INTFLOAT *temp = ac->temp;
    int i;

    // imdct
    if (ics->window_sequence[0] == EIGHT_SHORT_SEQUENCE) {
        for (i = 0; i < 1024; i += 128)
            ac->mdct_small.imdct_half(&ac->mdct_small, buf + i, in + i);
    } else {
        ac->mdct.imdct_half(&ac->mdct, buf, in);
#if USE_FIXED
        for (i=0; i<1024; i++)
          buf[i] = (buf[i] + 4LL) >> 3;
#endif /* USE_FIXED */
    }

    /* window overlapping
     * NOTE: To simplify the overlapping code, all 'meaningless' short to long
     * and long to short transitions are considered to be short to short
     * transitions. This leaves just two cases (long to long and short to short)
     * with a little special sauce for EIGHT_SHORT_SEQUENCE.
     */
    if ((ics->window_sequence[1] == ONLY_LONG_SEQUENCE || ics->window_sequence[1] == LONG_STOP_SEQUENCE) &&
            (ics->window_sequence[0] == ONLY_LONG_SEQUENCE || ics->window_sequence[0] == LONG_START_SEQUENCE)) {
        ac->fdsp->vector_fmul_window(    out,               saved,            buf,         lwindow_prev, 512);
    } else {
        memcpy(                         out,               saved,            448 * sizeof(*out));

        if (ics->window_sequence[0] == EIGHT_SHORT_SEQUENCE) {
            ac->fdsp->vector_fmul_window(out + 448 + 0*128, saved + 448,      buf + 0*128, swindow_prev, 64);
            ac->fdsp->vector_fmul_window(out + 448 + 1*128, buf + 0*128 + 64, buf + 1*128, swindow,      64);
            ac->fdsp->vector_fmul_window(out + 448 + 2*128, buf + 1*128 + 64, buf + 2*128, swindow,      64);
            ac->fdsp->vector_fmul_window(out + 448 + 3*128, buf + 2*128 + 64, buf + 3*128, swindow,      64);
            ac->fdsp->vector_fmul_window(temp,              buf + 3*128 + 64, buf + 4*128, swindow,      64);
            memcpy(                     out + 448 + 4*128, temp, 64 * sizeof(*out));
        } else {
            ac->fdsp->vector_fmul_window(out + 448,         saved + 448,      buf,         swindow_prev, 64);
            memcpy(                     out + 576,         buf + 64,         448 * sizeof(*out));
        }
    }

    // buffer update
    if (ics->window_sequence[0] == EIGHT_SHORT_SEQUENCE) {
        memcpy(                     saved,       temp + 64,         64 * sizeof(*saved));
        ac->fdsp->vector_fmul_window(saved + 64,  buf + 4*128 + 64, buf + 5*128, swindow, 64);
        ac->fdsp->vector_fmul_window(saved + 192, buf + 5*128 + 64, buf + 6*128, swindow, 64);
        ac->fdsp->vector_fmul_window(saved + 320, buf + 6*128 + 64, buf + 7*128, swindow, 64);
        memcpy(                     saved + 448, buf + 7*128 + 64,  64 * sizeof(*saved));
    } else if (ics->window_sequence[0] == LONG_START_SEQUENCE) {
        memcpy(                     saved,       buf + 512,        448 * sizeof(*saved));
        memcpy(                     saved + 448, buf + 7*128 + 64,  64 * sizeof(*saved));
    } else { // LONG_STOP or ONLY_LONG
        memcpy(                     saved,       buf + 512,        512 * sizeof(*saved));
    }
}