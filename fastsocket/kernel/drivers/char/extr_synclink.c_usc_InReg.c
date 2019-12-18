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
typedef  scalar_t__ u16 ;
struct mgsl_struct {scalar_t__ io_base; scalar_t__ loopback_bits; } ;

/* Variables and functions */
 scalar_t__ CCAR ; 
 scalar_t__ inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (scalar_t__,scalar_t__) ; 

__attribute__((used)) static u16 usc_InReg( struct mgsl_struct *info, u16 RegAddr )
{
	outw( RegAddr + info->loopback_bits, info->io_base + CCAR );
	return inw( info->io_base + CCAR );

}