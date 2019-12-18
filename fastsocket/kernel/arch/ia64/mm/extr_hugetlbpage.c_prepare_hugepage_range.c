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
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long HPAGE_MASK ; 
 scalar_t__ REGION_NUMBER (unsigned long) ; 
 scalar_t__ RGN_HPAGE ; 

int prepare_hugepage_range(struct file *file,
			unsigned long addr, unsigned long len)
{
	if (len & ~HPAGE_MASK)
		return -EINVAL;
	if (addr & ~HPAGE_MASK)
		return -EINVAL;
	if (REGION_NUMBER(addr) != RGN_HPAGE)
		return -EINVAL;

	return 0;
}