#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ioc3_uartregs {int dummy; } ;
struct TYPE_3__ {struct ioc3_uartregs uarta; } ;
struct ioc3 {TYPE_1__ sregs; } ;
typedef  scalar_t__ nasid_t ;
struct TYPE_4__ {scalar_t__ memory_base; } ;

/* Variables and functions */
 scalar_t__ INVALID_NASID ; 
 TYPE_2__* KL_CONFIG_CH_CONS_INFO (scalar_t__) ; 
 scalar_t__ get_nasid () ; 
 scalar_t__ master_nasid ; 

__attribute__((used)) static inline struct ioc3_uartregs *console_uart(void)
{
	struct ioc3 *ioc3;
	nasid_t nasid;

	nasid = (master_nasid == INVALID_NASID) ? get_nasid() : master_nasid;
	ioc3 = (struct ioc3 *)KL_CONFIG_CH_CONS_INFO(nasid)->memory_base;

	return &ioc3->sregs.uarta;
}