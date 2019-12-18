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
 scalar_t__ SYSCALL_VECTOR ; 
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ syscall_vector ; 
 int /*<<< orphan*/  used_vectors ; 

void free_interrupts(void)
{
	if (syscall_vector != SYSCALL_VECTOR)
		clear_bit(syscall_vector, used_vectors);
}