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
typedef  scalar_t__ __le16 ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ const cpu_to_le16 (int) ; 

__attribute__((used)) static int moxa_check_fw(const void *ptr)
{
	const __le16 *lptr = ptr;

	if (*lptr != cpu_to_le16(0x7980))
		return -EINVAL;

	return 0;
}