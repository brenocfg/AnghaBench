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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  OSBitAndAtomic (int /*<<< orphan*/ ,int /*<<< orphan*/  volatile*) ; 

__attribute__((used)) static uint32_t
flag_clear(volatile uint32_t *flags, uint32_t bit)
{
	return (OSBitAndAtomic(~bit, flags));
}