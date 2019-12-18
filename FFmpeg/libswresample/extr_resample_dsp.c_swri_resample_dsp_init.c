#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  resample_linear; int /*<<< orphan*/  resample_common; int /*<<< orphan*/  resample_one; } ;
struct TYPE_8__ {int format; TYPE_1__ dsp; } ;
typedef  TYPE_2__ ResampleContext ;

/* Variables and functions */
 scalar_t__ ARCH_AARCH64 ; 
 scalar_t__ ARCH_ARM ; 
 scalar_t__ ARCH_X86 ; 
#define  AV_SAMPLE_FMT_DBLP 131 
#define  AV_SAMPLE_FMT_FLTP 130 
#define  AV_SAMPLE_FMT_S16P 129 
#define  AV_SAMPLE_FMT_S32P 128 
 int /*<<< orphan*/  resample_common_double ; 
 int /*<<< orphan*/  resample_common_float ; 
 int /*<<< orphan*/  resample_common_int16 ; 
 int /*<<< orphan*/  resample_common_int32 ; 
 int /*<<< orphan*/  resample_linear_double ; 
 int /*<<< orphan*/  resample_linear_float ; 
 int /*<<< orphan*/  resample_linear_int16 ; 
 int /*<<< orphan*/  resample_linear_int32 ; 
 int /*<<< orphan*/  resample_one_double ; 
 int /*<<< orphan*/  resample_one_float ; 
 int /*<<< orphan*/  resample_one_int16 ; 
 int /*<<< orphan*/  resample_one_int32 ; 
 int /*<<< orphan*/  swri_resample_dsp_aarch64_init (TYPE_2__*) ; 
 int /*<<< orphan*/  swri_resample_dsp_arm_init (TYPE_2__*) ; 
 int /*<<< orphan*/  swri_resample_dsp_x86_init (TYPE_2__*) ; 

void swri_resample_dsp_init(ResampleContext *c)
{
    switch(c->format){
    case AV_SAMPLE_FMT_S16P:
        c->dsp.resample_one = resample_one_int16;
        c->dsp.resample_common = resample_common_int16;
        c->dsp.resample_linear = resample_linear_int16;
        break;
    case AV_SAMPLE_FMT_S32P:
        c->dsp.resample_one = resample_one_int32;
        c->dsp.resample_common = resample_common_int32;
        c->dsp.resample_linear = resample_linear_int32;
        break;
    case AV_SAMPLE_FMT_FLTP:
        c->dsp.resample_one = resample_one_float;
        c->dsp.resample_common = resample_common_float;
        c->dsp.resample_linear = resample_linear_float;
        break;
    case AV_SAMPLE_FMT_DBLP:
        c->dsp.resample_one = resample_one_double;
        c->dsp.resample_common = resample_common_double;
        c->dsp.resample_linear = resample_linear_double;
        break;
    }

    if (ARCH_X86) swri_resample_dsp_x86_init(c);
    else if (ARCH_ARM) swri_resample_dsp_arm_init(c);
    else if (ARCH_AARCH64) swri_resample_dsp_aarch64_init(c);
}