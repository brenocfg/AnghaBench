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
 int /*<<< orphan*/  SIO_UNLOCK_KEY ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void superio_enter(int base)
{
	/* according to the datasheet the key must be send twice! */
	outb( SIO_UNLOCK_KEY, base);
	outb( SIO_UNLOCK_KEY, base);
}