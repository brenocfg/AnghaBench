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
struct BusLogic_HostAdapter {scalar_t__ IO_Address; } ;

/* Variables and functions */
 scalar_t__ BusLogic_CommandParameterRegisterOffset ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 

__attribute__((used)) static inline void BusLogic_WriteCommandParameterRegister(struct BusLogic_HostAdapter
							  *HostAdapter, unsigned char Value)
{
	outb(Value, HostAdapter->IO_Address + BusLogic_CommandParameterRegisterOffset);
}