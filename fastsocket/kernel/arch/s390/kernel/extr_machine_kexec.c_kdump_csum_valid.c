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
struct kimage {scalar_t__ start; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  __raw_local_irq_stnsm (int) ; 
 int /*<<< orphan*/  __raw_local_irq_stosm (int) ; 

__attribute__((used)) static int kdump_csum_valid(struct kimage *image)
{
#ifdef CONFIG_CRASH_DUMP
	int (*start_kdump)(int) = (void *)image->start;
	int rc;

	__raw_local_irq_stnsm(0xfb); /* disable DAT */
	rc = start_kdump(0);
	__raw_local_irq_stosm(0x04); /* enable DAT */
	return rc ? 0 : -EINVAL;
#else
	return -EINVAL;
#endif
}