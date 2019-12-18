#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int clock_speed; } ;
struct TYPE_8__ {TYPE_1__ params; } ;
typedef  TYPE_2__ MGSLPC_INFO ;

/* Variables and functions */
 unsigned char BIT0 ; 
 unsigned char BIT1 ; 
 unsigned char BIT2 ; 
 unsigned char BIT4 ; 
 unsigned char BIT5 ; 
 scalar_t__ CCR1 ; 
 scalar_t__ CCR2 ; 
 scalar_t__ CHA ; 
 scalar_t__ MODE ; 
 int /*<<< orphan*/  mgslpc_set_rate (TYPE_2__*,scalar_t__,int) ; 
 unsigned char read_reg (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  write_reg (TYPE_2__*,scalar_t__,unsigned char) ; 

__attribute__((used)) static void loopback_enable(MGSLPC_INFO *info)
{
	unsigned char val;

	/* CCR1:02..00  CM[2..0] Clock Mode = 111 (clock mode 7) */
	val = read_reg(info, CHA + CCR1) | (BIT2 + BIT1 + BIT0);
	write_reg(info, CHA + CCR1, val);

	/* CCR2:04 SSEL Clock source select, 1=submode b */
	val = read_reg(info, CHA + CCR2) | (BIT4 + BIT5);
	write_reg(info, CHA + CCR2, val);

	/* set LinkSpeed if available, otherwise default to 2Mbps */
	if (info->params.clock_speed)
		mgslpc_set_rate(info, CHA, info->params.clock_speed);
	else
		mgslpc_set_rate(info, CHA, 1843200);

	/* MODE:00 TLP Test Loop, 1=loopback enabled */
	val = read_reg(info, CHA + MODE) | BIT0;
	write_reg(info, CHA + MODE, val);
}