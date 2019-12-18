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
typedef  int vme_address_t ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
#define  VME_A16 136 
 unsigned long long VME_A16_MAX ; 
#define  VME_A24 135 
 unsigned long long VME_A24_MAX ; 
#define  VME_A32 134 
 unsigned long long VME_A32_MAX ; 
#define  VME_A64 133 
#define  VME_CRCSR 132 
 unsigned long long VME_CRCSR_MAX ; 
#define  VME_USER1 131 
#define  VME_USER2 130 
#define  VME_USER3 129 
#define  VME_USER4 128 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int vme_check_window(vme_address_t aspace, unsigned long long vme_base,
	unsigned long long size)
{
	int retval = 0;

	switch (aspace) {
	case VME_A16:
		if (((vme_base + size) > VME_A16_MAX) ||
				(vme_base > VME_A16_MAX))
			retval = -EFAULT;
		break;
	case VME_A24:
		if (((vme_base + size) > VME_A24_MAX) ||
				(vme_base > VME_A24_MAX))
			retval = -EFAULT;
		break;
	case VME_A32:
		if (((vme_base + size) > VME_A32_MAX) ||
				(vme_base > VME_A32_MAX))
			retval = -EFAULT;
		break;
	case VME_A64:
		/*
		 * Any value held in an unsigned long long can be used as the
		 * base
		 */
		break;
	case VME_CRCSR:
		if (((vme_base + size) > VME_CRCSR_MAX) ||
				(vme_base > VME_CRCSR_MAX))
			retval = -EFAULT;
		break;
	case VME_USER1:
	case VME_USER2:
	case VME_USER3:
	case VME_USER4:
		/* User Defined */
		break;
	default:
		printk("Invalid address space\n");
		retval = -EINVAL;
		break;
	}

	return retval;
}