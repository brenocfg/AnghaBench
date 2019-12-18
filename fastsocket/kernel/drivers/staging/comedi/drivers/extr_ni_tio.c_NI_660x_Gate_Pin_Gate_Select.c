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
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int ni_660x_max_gate_pin ; 

__attribute__((used)) static inline unsigned NI_660x_Gate_Pin_Gate_Select(unsigned n)
{
	BUG_ON(n > ni_660x_max_gate_pin);
	return 0x2 + n;
}