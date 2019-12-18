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
 int /*<<< orphan*/  M32R_SIO0_CR_PORTL ; 
 int __sio_in (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int /*<<< orphan*/  sio_init () ; 

__attribute__((used)) static void sio_error(int *status)
{
	printk("SIO0 error[%04x]\n", *status);
	do {
		sio_init();
	} while ((*status = __sio_in(M32R_SIO0_CR_PORTL)) != 3);
}