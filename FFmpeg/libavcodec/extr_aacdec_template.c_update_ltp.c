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
struct TYPE_10__ {int /*<<< orphan*/ * buf_mdct; TYPE_1__* fdsp; } ;
struct TYPE_9__ {scalar_t__* window_sequence; scalar_t__* use_kb_window; } ;
struct TYPE_8__ {int /*<<< orphan*/ * ltp_state; int /*<<< orphan*/ * ret; int /*<<< orphan*/ * coeffs; int /*<<< orphan*/ * saved; TYPE_3__ ics; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* vector_fmul_reverse ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ;} ;
typedef  TYPE_2__ SingleChannelElement ;
typedef  TYPE_3__ IndividualChannelStream ;
typedef  int /*<<< orphan*/  INTFLOAT ;
typedef  TYPE_4__ AACContext ;

/* Variables and functions */
 int /*<<< orphan*/  AAC_MUL31 (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/ * AAC_RENAME (int /*<<< orphan*/ ) ; 
 scalar_t__ EIGHT_SHORT_SEQUENCE ; 
 scalar_t__ LONG_START_SEQUENCE ; 
 int /*<<< orphan*/  ff_aac_kbd_long_1024 ; 
 int /*<<< orphan*/  ff_aac_kbd_short_128 ; 
 int /*<<< orphan*/  ff_sine_1024 ; 
 int /*<<< orphan*/  ff_sine_128 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void update_ltp(AACContext *ac, SingleChannelElement *sce)
{
    IndividualChannelStream *ics = &sce->ics;
    INTFLOAT *saved     = sce->saved;
    INTFLOAT *saved_ltp = sce->coeffs;
    const INTFLOAT *lwindow = ics->use_kb_window[0] ? AAC_RENAME(ff_aac_kbd_long_1024) : AAC_RENAME(ff_sine_1024);
    const INTFLOAT *swindow = ics->use_kb_window[0] ? AAC_RENAME(ff_aac_kbd_short_128) : AAC_RENAME(ff_sine_128);
    int i;

    if (ics->window_sequence[0] == EIGHT_SHORT_SEQUENCE) {
        memcpy(saved_ltp,       saved, 512 * sizeof(*saved_ltp));
        memset(saved_ltp + 576, 0,     448 * sizeof(*saved_ltp));
        ac->fdsp->vector_fmul_reverse(saved_ltp + 448, ac->buf_mdct + 960,     &swindow[64],      64);

        for (i = 0; i < 64; i++)
            saved_ltp[i + 512] = AAC_MUL31(ac->buf_mdct[1023 - i], swindow[63 - i]);
    } else if (ics->window_sequence[0] == LONG_START_SEQUENCE) {
        memcpy(saved_ltp,       ac->buf_mdct + 512, 448 * sizeof(*saved_ltp));
        memset(saved_ltp + 576, 0,                  448 * sizeof(*saved_ltp));
        ac->fdsp->vector_fmul_reverse(saved_ltp + 448, ac->buf_mdct + 960,     &swindow[64],      64);

        for (i = 0; i < 64; i++)
            saved_ltp[i + 512] = AAC_MUL31(ac->buf_mdct[1023 - i], swindow[63 - i]);
    } else { // LONG_STOP or ONLY_LONG
        ac->fdsp->vector_fmul_reverse(saved_ltp,       ac->buf_mdct + 512,     &lwindow[512],     512);

        for (i = 0; i < 512; i++)
            saved_ltp[i + 512] = AAC_MUL31(ac->buf_mdct[1023 - i], lwindow[511 - i]);
    }

    memcpy(sce->ltp_state,      sce->ltp_state+1024, 1024 * sizeof(*sce->ltp_state));
    memcpy(sce->ltp_state+1024, sce->ret,            1024 * sizeof(*sce->ltp_state));
    memcpy(sce->ltp_state+2048, saved_ltp,           1024 * sizeof(*sce->ltp_state));
}