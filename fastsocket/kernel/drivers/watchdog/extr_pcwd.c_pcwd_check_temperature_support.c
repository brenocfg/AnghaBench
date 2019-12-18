#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int supports_temp; int /*<<< orphan*/  io_addr; } ;

/* Variables and functions */
 int inb (int /*<<< orphan*/ ) ; 
 TYPE_1__ pcwd_private ; 

__attribute__((used)) static inline void pcwd_check_temperature_support(void)
{
	if (inb(pcwd_private.io_addr) != 0xF0)
		pcwd_private.supports_temp = 1;
}