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
 int /*<<< orphan*/  CORGI_GPIO_AC_IN ; 
 int /*<<< orphan*/  CORGI_GPIO_KEY_INT ; 
 int /*<<< orphan*/  CORGI_GPIO_WAKEUP ; 
 unsigned long GPIO_bit (int /*<<< orphan*/ ) ; 
 unsigned long GPLR0 ; 

__attribute__((used)) static unsigned long corgi_charger_wakeup(void)
{
	return ~GPLR0 & ( GPIO_bit(CORGI_GPIO_AC_IN) | GPIO_bit(CORGI_GPIO_KEY_INT) | GPIO_bit(CORGI_GPIO_WAKEUP) );
}