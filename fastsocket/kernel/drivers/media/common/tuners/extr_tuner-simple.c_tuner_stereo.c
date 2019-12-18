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

/* Variables and functions */
#define  TUNER_LG_NTSC_TAPE 133 
#define  TUNER_PHILIPS_FM1216ME_MK3 132 
#define  TUNER_PHILIPS_FM1216MK5 131 
#define  TUNER_PHILIPS_FM1236_MK3 130 
#define  TUNER_PHILIPS_FM1256_IH3 129 
 int const TUNER_SIGNAL ; 
 int const TUNER_STEREO ; 
 int const TUNER_STEREO_MK3 ; 
#define  TUNER_TCL_MF02GIP_5N 128 

__attribute__((used)) static inline int tuner_stereo(const int type, const int status)
{
	switch (type) {
	case TUNER_PHILIPS_FM1216ME_MK3:
	case TUNER_PHILIPS_FM1236_MK3:
	case TUNER_PHILIPS_FM1256_IH3:
	case TUNER_LG_NTSC_TAPE:
	case TUNER_TCL_MF02GIP_5N:
		return ((status & TUNER_SIGNAL) == TUNER_STEREO_MK3);
	case TUNER_PHILIPS_FM1216MK5:
		return status | TUNER_STEREO;
	default:
		return status & TUNER_STEREO;
	}
}