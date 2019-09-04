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
 int /*<<< orphan*/  __wake (scalar_t__*,int,int) ; 
 int a_fetch_add (scalar_t__*,int) ; 
 scalar_t__* vmlock ; 

void __vm_unlock()
{
	if (a_fetch_add(vmlock, -1)==1 && vmlock[1])
		__wake(vmlock, -1, 1);
}