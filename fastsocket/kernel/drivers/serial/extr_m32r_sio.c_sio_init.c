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
 int /*<<< orphan*/  M32R_SIO0_RXB_PORTL ; 
 int /*<<< orphan*/  M32R_SIO0_STS_PORTL ; 
 unsigned int __sio_in (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __sio_out (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sio_init(void)
{
	unsigned int tmp;

	tmp = __sio_in(M32R_SIO0_RXB_PORTL);
	tmp = __sio_in(M32R_SIO0_RXB_PORTL);
	tmp = __sio_in(M32R_SIO0_STS_PORTL);
	__sio_out(0x00000003, M32R_SIO0_CR_PORTL);
}