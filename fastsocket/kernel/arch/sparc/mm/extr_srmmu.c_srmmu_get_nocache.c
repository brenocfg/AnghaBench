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
 unsigned long __srmmu_get_nocache (int,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned long srmmu_get_nocache(int size, int align)
{
	unsigned long tmp;

	tmp = __srmmu_get_nocache(size, align);

	if (tmp)
		memset((void *)tmp, 0, size);

	return tmp;
}