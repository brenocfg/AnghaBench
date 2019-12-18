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
#define  BCM57712_VF 132 
#define  BCM57800_VF 131 
#define  BCM57810_VF 130 
#define  BCM57811_VF 129 
#define  BCM57840_VF 128 

__attribute__((used)) static int set_is_vf(int chip_id)
{
	switch (chip_id) {
	case BCM57712_VF:
	case BCM57800_VF:
	case BCM57810_VF:
	case BCM57840_VF:
	case BCM57811_VF:
		return true;
	default:
		return false;
	}
}