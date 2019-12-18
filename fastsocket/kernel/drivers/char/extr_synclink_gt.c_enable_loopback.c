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
struct TYPE_2__ {scalar_t__ mode; int clock_speed; } ;
struct slgt_info {TYPE_1__ params; } ;

/* Variables and functions */
 int BIT2 ; 
 int /*<<< orphan*/  CCR ; 
 scalar_t__ MGSL_MODE_ASYNC ; 
 int /*<<< orphan*/  SCR ; 
 int rd_reg16 (struct slgt_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_rate (struct slgt_info*,int) ; 
 int /*<<< orphan*/  wr_reg16 (struct slgt_info*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  wr_reg8 (struct slgt_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void enable_loopback(struct slgt_info *info)
{
	/* SCR (serial control) BIT2=looopback enable */
	wr_reg16(info, SCR, (unsigned short)(rd_reg16(info, SCR) | BIT2));

	if (info->params.mode != MGSL_MODE_ASYNC) {
		/* CCR (clock control)
		 * 07..05  tx clock source (010 = BRG)
		 * 04..02  rx clock source (010 = BRG)
		 * 01      auxclk enable   (0 = disable)
		 * 00      BRG enable      (1 = enable)
		 *
		 * 0100 1001
		 */
		wr_reg8(info, CCR, 0x49);

		/* set speed if available, otherwise use default */
		if (info->params.clock_speed)
			set_rate(info, info->params.clock_speed);
		else
			set_rate(info, 3686400);
	}
}