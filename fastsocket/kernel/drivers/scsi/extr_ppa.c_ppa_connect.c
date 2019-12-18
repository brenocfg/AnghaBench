#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned short base; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ ppa_struct ;

/* Variables and functions */
 int CONNECT_EPP_MAYBE ; 
 scalar_t__ IN_EPP_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppa_c_pulse (unsigned short,int) ; 

__attribute__((used)) static inline void ppa_connect(ppa_struct *dev, int flag)
{
	unsigned short ppb = dev->base;

	ppa_c_pulse(ppb, 0);
	ppa_c_pulse(ppb, 0x3c);
	ppa_c_pulse(ppb, 0x20);
	if ((flag == CONNECT_EPP_MAYBE) && IN_EPP_MODE(dev->mode))
		ppa_c_pulse(ppb, 0xcf);
	else
		ppa_c_pulse(ppb, 0x8f);
}