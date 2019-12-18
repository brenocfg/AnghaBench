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
typedef  size_t u16 ;

/* Variables and functions */
 size_t IVB_GMCH_GMS_MASK ; 
 size_t IVB_GMCH_GMS_SHIFT ; 

__attribute__((used)) static inline size_t gen7_get_stolen_size(u16 snb_gmch_ctl)
{
	static const int stolen_decoder[] = {
		0, 0, 0, 0, 0, 32, 48, 64, 128, 256, 96, 160, 224, 352};
	snb_gmch_ctl >>= IVB_GMCH_GMS_SHIFT;
	snb_gmch_ctl &= IVB_GMCH_GMS_MASK;
	return stolen_decoder[snb_gmch_ctl] << 20;
}