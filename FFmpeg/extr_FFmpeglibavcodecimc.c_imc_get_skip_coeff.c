#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int* skipFlagBits; int* skipFlagCount; int* skipFlags; int /*<<< orphan*/ * skipFlagRaw; int /*<<< orphan*/ * bandWidthT; int /*<<< orphan*/ * bandFlagsBuf; } ;
struct TYPE_5__ {int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ IMCContext ;
typedef  TYPE_2__ IMCChannel ;

/* Variables and functions */
 int BANDS ; 
 int* band_tab ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void imc_get_skip_coeff(IMCContext *q, IMCChannel *chctx)
{
    int i, j;

    memset(chctx->skipFlagBits,  0, sizeof(chctx->skipFlagBits));
    memset(chctx->skipFlagCount, 0, sizeof(chctx->skipFlagCount));
    for (i = 0; i < BANDS; i++) {
        if (!chctx->bandFlagsBuf[i] || !chctx->bandWidthT[i])
            continue;

        if (!chctx->skipFlagRaw[i]) {
            chctx->skipFlagBits[i] = band_tab[i + 1] - band_tab[i];

            for (j = band_tab[i]; j < band_tab[i + 1]; j++) {
                chctx->skipFlags[j] = get_bits1(&q->gb);
                if (chctx->skipFlags[j])
                    chctx->skipFlagCount[i]++;
            }
        } else {
            for (j = band_tab[i]; j < band_tab[i + 1] - 1; j += 2) {
                if (!get_bits1(&q->gb)) { // 0
                    chctx->skipFlagBits[i]++;
                    chctx->skipFlags[j]      = 1;
                    chctx->skipFlags[j + 1]  = 1;
                    chctx->skipFlagCount[i] += 2;
                } else {
                    if (get_bits1(&q->gb)) { // 11
                        chctx->skipFlagBits[i] += 2;
                        chctx->skipFlags[j]     = 0;
                        chctx->skipFlags[j + 1] = 1;
                        chctx->skipFlagCount[i]++;
                    } else {
                        chctx->skipFlagBits[i] += 3;
                        chctx->skipFlags[j + 1] = 0;
                        if (!get_bits1(&q->gb)) { // 100
                            chctx->skipFlags[j] = 1;
                            chctx->skipFlagCount[i]++;
                        } else { // 101
                            chctx->skipFlags[j] = 0;
                        }
                    }
                }
            }

            if (j < band_tab[i + 1]) {
                chctx->skipFlagBits[i]++;
                if ((chctx->skipFlags[j] = get_bits1(&q->gb)))
                    chctx->skipFlagCount[i]++;
            }
        }
    }
}