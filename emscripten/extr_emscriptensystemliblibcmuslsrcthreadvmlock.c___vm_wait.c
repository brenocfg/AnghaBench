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
 int /*<<< orphan*/  __wait (int*,int*,int,int) ; 
 int* vmlock ; 

void __vm_wait()
{
	int tmp;
	while ((tmp=vmlock[0]))
		__wait(vmlock, vmlock+1, tmp, 1);
}