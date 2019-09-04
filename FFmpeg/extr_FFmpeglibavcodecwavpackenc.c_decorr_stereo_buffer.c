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
struct Decorr {int delta; int value; int weightA; int weightB; int sumA; int sumB; int /*<<< orphan*/  samplesB; int /*<<< orphan*/  samplesA; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_3__ {scalar_t__ gt16bit; struct Decorr* dps; } ;
typedef  TYPE_1__ WavPackExtraInfo ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR (int /*<<< orphan*/ ) ; 
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  decorr_stereo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,struct Decorr*,int) ; 
 int /*<<< orphan*/  decorr_stereo_quick (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,struct Decorr*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reverse_decorr (struct Decorr*) ; 

__attribute__((used)) static void decorr_stereo_buffer(WavPackExtraInfo *info,
                                 int32_t *in_left,  int32_t *in_right,
                                 int32_t *out_left, int32_t *out_right,
                                 int nb_samples, int tindex)
{
    struct Decorr dp = {0}, *dppi = info->dps + tindex;
    int delta = dppi->delta, pre_delta;
    int term = dppi->value;

    if (delta == 7)
        pre_delta = 7;
    else if (delta < 2)
        pre_delta = 3;
    else
        pre_delta = delta + 1;

    dp.value = term;
    dp.delta = pre_delta;
    decorr_stereo(in_left, in_right, out_left, out_right,
                  FFMIN(2048, nb_samples), &dp, -1);
    dp.delta = delta;

    if (tindex == 0) {
        reverse_decorr(&dp);
    } else {
        CLEAR(dp.samplesA);
        CLEAR(dp.samplesB);
    }

    memcpy(dppi->samplesA, dp.samplesA, sizeof(dp.samplesA));
    memcpy(dppi->samplesB, dp.samplesB, sizeof(dp.samplesB));
    dppi->weightA = dp.weightA;
    dppi->weightB = dp.weightB;

    if (delta == 0) {
        dp.delta = 1;
        decorr_stereo(in_left, in_right, out_left, out_right, nb_samples, &dp, 1);
        dp.delta = 0;
        memcpy(dp.samplesA, dppi->samplesA, sizeof(dp.samplesA));
        memcpy(dp.samplesB, dppi->samplesB, sizeof(dp.samplesB));
        dppi->weightA = dp.weightA = dp.sumA / nb_samples;
        dppi->weightB = dp.weightB = dp.sumB / nb_samples;
    }

    if (info->gt16bit)
        decorr_stereo(in_left, in_right, out_left, out_right,
                           nb_samples, &dp, 1);
    else
        decorr_stereo_quick(in_left, in_right, out_left, out_right,
                            nb_samples, &dp);
}