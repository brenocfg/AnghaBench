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
 int EINVAL ; 
#define  IPQ_COPY_META 130 
#define  IPQ_COPY_NONE 129 
#define  IPQ_COPY_PACKET 128 
 unsigned char copy_mode ; 
 int copy_range ; 

__attribute__((used)) static inline int
__ipq_set_mode(unsigned char mode, unsigned int range)
{
	int status = 0;

	switch(mode) {
	case IPQ_COPY_NONE:
	case IPQ_COPY_META:
		copy_mode = mode;
		copy_range = 0;
		break;

	case IPQ_COPY_PACKET:
		copy_mode = mode;
		copy_range = range;
		if (copy_range > 0xFFFF)
			copy_range = 0xFFFF;
		break;

	default:
		status = -EINVAL;

	}
	return status;
}