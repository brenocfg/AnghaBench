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
 int /*<<< orphan*/  CIR_DR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WDTS_KEEPALIVE ; 
 int /*<<< orphan*/  WDTS_USE_GP ; 
 int /*<<< orphan*/  base ; 
 int /*<<< orphan*/  inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdt_status ; 

__attribute__((used)) static void wdt_keepalive(void)
{
	if (test_bit(WDTS_USE_GP, &wdt_status))
		inb(base);
	else
		/* The timer reloads with around 5 msec delay */
		outb(0x55, CIR_DR(base));
	set_bit(WDTS_KEEPALIVE, &wdt_status);
}