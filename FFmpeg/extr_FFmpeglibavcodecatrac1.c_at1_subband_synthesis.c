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
struct TYPE_6__ {float** bands; } ;
struct TYPE_5__ {float* last_qmf_delay; int /*<<< orphan*/  snd_qmf_delay; int /*<<< orphan*/  fst_qmf_delay; } ;
typedef  TYPE_1__ AT1SUCtx ;
typedef  TYPE_2__ AT1Ctx ;

/* Variables and functions */
 int /*<<< orphan*/  ff_atrac_iqmf (float*,float*,int,float*,int /*<<< orphan*/ ,float*) ; 
 int /*<<< orphan*/  memcpy (float*,float*,int) ; 

__attribute__((used)) static void at1_subband_synthesis(AT1Ctx *q, AT1SUCtx* su, float *pOut)
{
    float temp[256];
    float iqmf_temp[512 + 46];

    /* combine low and middle bands */
    ff_atrac_iqmf(q->bands[0], q->bands[1], 128, temp, su->fst_qmf_delay, iqmf_temp);

    /* delay the signal of the high band by 39 samples */
    memcpy( su->last_qmf_delay,    &su->last_qmf_delay[256], sizeof(float) *  39);
    memcpy(&su->last_qmf_delay[39], q->bands[2],             sizeof(float) * 256);

    /* combine (low + middle) and high bands */
    ff_atrac_iqmf(temp, su->last_qmf_delay, 256, pOut, su->snd_qmf_delay, iqmf_temp);
}