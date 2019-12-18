#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int supported_devices; int model; int* levels; } ;
typedef  TYPE_1__ sb_devc ;

/* Variables and functions */
 int EINVAL ; 
#define  MDL_ESS 129 
#define  MDL_SMW 128 
 int ess_mixer_set (TYPE_1__*,int,int,int) ; 
 int sb_common_mixer_set (TYPE_1__*,int,int,int) ; 
 int smw_mixer_set (TYPE_1__*,int,int,int) ; 

__attribute__((used)) static int sb_mixer_set(sb_devc * devc, int dev, int value)
{
	int left = value & 0x000000ff;
	int right = (value & 0x0000ff00) >> 8;
	int retval;

	if (left > 100)
		left = 100;
	if (right > 100)
		right = 100;

	if ((dev < 0) || (dev > 31))
		return -EINVAL;

	if (!(devc->supported_devices & (1 << dev)))	/*
							 * Not supported
							 */
		return -EINVAL;

	/* Differentiate depending on the chipsets */
	switch (devc->model) {
	case MDL_SMW:
		retval = smw_mixer_set(devc, dev, left, right);
		break;
	case MDL_ESS:
		retval = ess_mixer_set(devc, dev, left, right);
		break;
	default:
		retval = sb_common_mixer_set(devc, dev, left, right);
	}
	if (retval >= 0) devc->levels[dev] = retval;

	return retval;
}