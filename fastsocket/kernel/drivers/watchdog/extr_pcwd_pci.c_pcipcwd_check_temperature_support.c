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
 int inb_p (int /*<<< orphan*/ ) ; 
 TYPE_1__ pcipcwd_private ; 

__attribute__((used)) static inline void pcipcwd_check_temperature_support(void)
{
	if (inb_p(pcipcwd_private.io_addr) != 0xF0)
		pcipcwd_private.supports_temp = 1;
}