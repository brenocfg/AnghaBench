#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  enum MVModes { ____Placeholder_MVModes } MVModes ;

/* Variables and functions */
#define  MV_PMODE_1MV 132 
#define  MV_PMODE_1MV_HPEL 131 
#define  MV_PMODE_1MV_HPEL_BILIN 130 
#define  MV_PMODE_INTENSITY_COMP 129 
#define  MV_PMODE_MIXED_MV 128 
 int VAMvMode1Mv ; 
 int VAMvMode1MvHalfPel ; 
 int VAMvMode1MvHalfPelBilinear ; 
 int VAMvModeIntensityCompensation ; 
 int VAMvModeMixedMv ; 

__attribute__((used)) static int get_VAMvModeVC1(enum MVModes mv_mode)
{
    switch (mv_mode) {
    case MV_PMODE_1MV_HPEL_BILIN: return VAMvMode1MvHalfPelBilinear;
    case MV_PMODE_1MV:            return VAMvMode1Mv;
    case MV_PMODE_1MV_HPEL:       return VAMvMode1MvHalfPel;
    case MV_PMODE_MIXED_MV:       return VAMvModeMixedMv;
    case MV_PMODE_INTENSITY_COMP: return VAMvModeIntensityCompensation;
    }
    return 0;
}