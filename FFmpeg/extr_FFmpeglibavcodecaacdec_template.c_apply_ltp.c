#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int int16_t ;
typedef  scalar_t__ UINTFLOAT ;
struct TYPE_11__ {int lag; scalar_t__* used; int /*<<< orphan*/  coef; } ;
struct TYPE_14__ {int* swb_offset; scalar_t__* window_sequence; int /*<<< orphan*/  max_sfb; TYPE_2__ ltp; } ;
struct TYPE_13__ {scalar_t__ present; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* apply_tns ) (scalar_t__*,TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* windowing_and_mdct_ltp ) (TYPE_3__*,scalar_t__*,scalar_t__*,TYPE_5__*) ;scalar_t__* buf_mdct; } ;
struct TYPE_10__ {int /*<<< orphan*/ * coeffs; TYPE_5__ ics; TYPE_4__ tns; int /*<<< orphan*/ * ltp_state; scalar_t__* ret; } ;
typedef  TYPE_1__ SingleChannelElement ;
typedef  TYPE_2__ LongTermPrediction ;
typedef  scalar_t__ INTFLOAT ;
typedef  TYPE_3__ AACContext ;

/* Variables and functions */
 scalar_t__ AAC_MUL30 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ EIGHT_SHORT_SEQUENCE ; 
 int FFMIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_LTP_LONG_SFB ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,scalar_t__*,scalar_t__*,TYPE_5__*) ; 
 int /*<<< orphan*/  stub2 (scalar_t__*,TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void apply_ltp(AACContext *ac, SingleChannelElement *sce)
{
    const LongTermPrediction *ltp = &sce->ics.ltp;
    const uint16_t *offsets = sce->ics.swb_offset;
    int i, sfb;

    if (sce->ics.window_sequence[0] != EIGHT_SHORT_SEQUENCE) {
        INTFLOAT *predTime = sce->ret;
        INTFLOAT *predFreq = ac->buf_mdct;
        int16_t num_samples = 2048;

        if (ltp->lag < 1024)
            num_samples = ltp->lag + 1024;
        for (i = 0; i < num_samples; i++)
            predTime[i] = AAC_MUL30(sce->ltp_state[i + 2048 - ltp->lag], ltp->coef);
        memset(&predTime[i], 0, (2048 - i) * sizeof(*predTime));

        ac->windowing_and_mdct_ltp(ac, predFreq, predTime, &sce->ics);

        if (sce->tns.present)
            ac->apply_tns(predFreq, &sce->tns, &sce->ics, 0);

        for (sfb = 0; sfb < FFMIN(sce->ics.max_sfb, MAX_LTP_LONG_SFB); sfb++)
            if (ltp->used[sfb])
                for (i = offsets[sfb]; i < offsets[sfb + 1]; i++)
                    sce->coeffs[i] += (UINTFLOAT)predFreq[i];
    }
}