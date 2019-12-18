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
 int /*<<< orphan*/  BAUD_RATE ; 
 int /*<<< orphan*/  M32R_SIO0_CR_PORTL ; 
 int /*<<< orphan*/  M32R_SIO0_MOD0_PORTL ; 
 int /*<<< orphan*/  M32R_SIO0_MOD1_PORTL ; 
 int /*<<< orphan*/  M32R_SIO0_TRCR_PORTL ; 
 int /*<<< orphan*/  __sio_out (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sio_set_baud_rate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sio_reset(void)
{
	__sio_out(0x00000300, M32R_SIO0_CR_PORTL);	/* init status */
	__sio_out(0x00000800, M32R_SIO0_MOD1_PORTL);	/* 8bit        */
	__sio_out(0x00000080, M32R_SIO0_MOD0_PORTL);	/* 1stop non   */
	sio_set_baud_rate(BAUD_RATE);
	__sio_out(0x00000000, M32R_SIO0_TRCR_PORTL);
	__sio_out(0x00000003, M32R_SIO0_CR_PORTL);	/* RXCEN */
}