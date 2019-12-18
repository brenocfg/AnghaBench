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
 unsigned int SYSCALL_VECTOR ; 
 unsigned int syscall_vector ; 

__attribute__((used)) static bool could_be_syscall(unsigned int num)
{
	/* Normal Linux SYSCALL_VECTOR or reserved vector? */
	return num == SYSCALL_VECTOR || num == syscall_vector;
}