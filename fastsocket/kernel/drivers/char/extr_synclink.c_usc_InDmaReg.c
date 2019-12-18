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
struct mgsl_struct {int /*<<< orphan*/  io_base; scalar_t__ mbre_bit; } ;

/* Variables and functions */
 scalar_t__ inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 usc_InDmaReg( struct mgsl_struct *info, u16 RegAddr )
{
	/* Note: The DCAR is located at the adapter base address */
	/* Note: must preserve state of BIT8 in DCAR */

	outw( RegAddr + info->mbre_bit, info->io_base );
	return inw( info->io_base );

}