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
typedef  int /*<<< orphan*/  thread_t ;
typedef  int /*<<< orphan*/  thread_continue_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MAXPRI_KERNEL ; 
 int SERIALMODE_INPUT ; 
 scalar_t__ kernel_thread_start_priority (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kprintf (char*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ serial_keyboard_start ; 
 int serialmode ; 
 int /*<<< orphan*/  thread_deallocate (int /*<<< orphan*/ ) ; 

void
serial_keyboard_init(void)
{
	kern_return_t	result;
	thread_t		thread;

	if(!(serialmode & SERIALMODE_INPUT)) /* Leave if we do not want a serial console */
		return;

	kprintf("Serial keyboard started\n");
	result = kernel_thread_start_priority((thread_continue_t)serial_keyboard_start, NULL, MAXPRI_KERNEL, &thread);
	if (result != KERN_SUCCESS)
		panic("serial_keyboard_init");

	thread_deallocate(thread);
}