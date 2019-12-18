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
#define  ARPHRD_INFINIBAND 128 

__attribute__((used)) static int ndisc_addr_option_pad(unsigned short type)
{
	switch (type) {
	case ARPHRD_INFINIBAND: return 2;
	default:                return 0;
	}
}