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
struct TYPE_6__ {float* flcoeffs1; scalar_t__* flcoeffs5; float* flcoeffs4; float* flcoeffs3; int* bandWidthT; int* bitsBandT; int* CWlengthT; } ;
struct TYPE_5__ {int /*<<< orphan*/  avctx; } ;
typedef  TYPE_1__ IMCContext ;
typedef  TYPE_2__ IMCChannel ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int BANDS ; 
 float FFMAX (float,float) ; 
 int av_clipf (double,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int* band_tab ; 
 float log2f (scalar_t__) ; 
 scalar_t__* xTab ; 

__attribute__((used)) static int bit_allocation(IMCContext *q, IMCChannel *chctx,
                          int stream_format_code, int freebits, int flag)
{
    int i, j;
    const float limit = -1.e20;
    float highest = 0.0;
    int indx;
    int t1 = 0;
    int t2 = 1;
    float summa = 0.0;
    int iacc = 0;
    int summer = 0;
    int rres, cwlen;
    float lowest = 1.e10;
    int low_indx = 0;
    float workT[32];
    int flg;
    int found_indx = 0;

    for (i = 0; i < BANDS; i++)
        highest = FFMAX(highest, chctx->flcoeffs1[i]);

    for (i = 0; i < BANDS - 1; i++) {
        if (chctx->flcoeffs5[i] <= 0) {
            av_log(q->avctx, AV_LOG_ERROR, "flcoeffs5 %f invalid\n", chctx->flcoeffs5[i]);
            return AVERROR_INVALIDDATA;
        }
        chctx->flcoeffs4[i] = chctx->flcoeffs3[i] - log2f(chctx->flcoeffs5[i]);
    }
    chctx->flcoeffs4[BANDS - 1] = limit;

    highest = highest * 0.25;

    for (i = 0; i < BANDS; i++) {
        indx = -1;
        if ((band_tab[i + 1] - band_tab[i]) == chctx->bandWidthT[i])
            indx = 0;

        if ((band_tab[i + 1] - band_tab[i]) > chctx->bandWidthT[i])
            indx = 1;

        if (((band_tab[i + 1] - band_tab[i]) / 2) >= chctx->bandWidthT[i])
            indx = 2;

        if (indx == -1)
            return AVERROR_INVALIDDATA;

        chctx->flcoeffs4[i] += xTab[(indx * 2 + (chctx->flcoeffs1[i] < highest)) * 2 + flag];
    }

    if (stream_format_code & 0x2) {
        chctx->flcoeffs4[0] = limit;
        chctx->flcoeffs4[1] = limit;
        chctx->flcoeffs4[2] = limit;
        chctx->flcoeffs4[3] = limit;
    }

    for (i = (stream_format_code & 0x2) ? 4 : 0; i < BANDS - 1; i++) {
        iacc  += chctx->bandWidthT[i];
        summa += chctx->bandWidthT[i] * chctx->flcoeffs4[i];
    }

    if (!iacc)
        return AVERROR_INVALIDDATA;

    chctx->bandWidthT[BANDS - 1] = 0;
    summa = (summa * 0.5 - freebits) / iacc;


    for (i = 0; i < BANDS / 2; i++) {
        rres = summer - freebits;
        if ((rres >= -8) && (rres <= 8))
            break;

        summer = 0;
        iacc   = 0;

        for (j = (stream_format_code & 0x2) ? 4 : 0; j < BANDS; j++) {
            cwlen = av_clipf(((chctx->flcoeffs4[j] * 0.5) - summa + 0.5), 0, 6);

            chctx->bitsBandT[j] = cwlen;
            summer += chctx->bandWidthT[j] * cwlen;

            if (cwlen > 0)
                iacc += chctx->bandWidthT[j];
        }

        flg = t2;
        t2 = 1;
        if (freebits < summer)
            t2 = -1;
        if (i == 0)
            flg = t2;
        if (flg != t2)
            t1++;

        summa = (float)(summer - freebits) / ((t1 + 1) * iacc) + summa;
    }

    for (i = (stream_format_code & 0x2) ? 4 : 0; i < BANDS; i++) {
        for (j = band_tab[i]; j < band_tab[i + 1]; j++)
            chctx->CWlengthT[j] = chctx->bitsBandT[i];
    }

    if (freebits > summer) {
        for (i = 0; i < BANDS; i++) {
            workT[i] = (chctx->bitsBandT[i] == 6) ? -1.e20
                                              : (chctx->bitsBandT[i] * -2 + chctx->flcoeffs4[i] - 0.415);
        }

        highest = 0.0;

        do {
            if (highest <= -1.e20)
                break;

            found_indx = 0;
            highest = -1.e20;

            for (i = 0; i < BANDS; i++) {
                if (workT[i] > highest) {
                    highest = workT[i];
                    found_indx = i;
                }
            }

            if (highest > -1.e20) {
                workT[found_indx] -= 2.0;
                if (++chctx->bitsBandT[found_indx] == 6)
                    workT[found_indx] = -1.e20;

                for (j = band_tab[found_indx]; j < band_tab[found_indx + 1] && (freebits > summer); j++) {
                    chctx->CWlengthT[j]++;
                    summer++;
                }
            }
        } while (freebits > summer);
    }
    if (freebits < summer) {
        for (i = 0; i < BANDS; i++) {
            workT[i] = chctx->bitsBandT[i] ? (chctx->bitsBandT[i] * -2 + chctx->flcoeffs4[i] + 1.585)
                                       : 1.e20;
        }
        if (stream_format_code & 0x2) {
            workT[0] = 1.e20;
            workT[1] = 1.e20;
            workT[2] = 1.e20;
            workT[3] = 1.e20;
        }
        while (freebits < summer) {
            lowest   = 1.e10;
            low_indx = 0;
            for (i = 0; i < BANDS; i++) {
                if (workT[i] < lowest) {
                    lowest   = workT[i];
                    low_indx = i;
                }
            }
            // if (lowest >= 1.e10)
            //     break;
            workT[low_indx] = lowest + 2.0;

            if (!--chctx->bitsBandT[low_indx])
                workT[low_indx] = 1.e20;

            for (j = band_tab[low_indx]; j < band_tab[low_indx+1] && (freebits < summer); j++) {
                if (chctx->CWlengthT[j] > 0) {
                    chctx->CWlengthT[j]--;
                    summer--;
                }
            }
        }
    }
    return 0;
}