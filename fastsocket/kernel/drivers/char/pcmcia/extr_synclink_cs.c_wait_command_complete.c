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
typedef  int /*<<< orphan*/  MGSLPC_INFO ;

/* Variables and functions */
 int BIT2 ; 
 scalar_t__ STAR ; 
 int read_reg (int /*<<< orphan*/ *,unsigned char) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static bool wait_command_complete(MGSLPC_INFO *info, unsigned char channel)
{
	int i = 0;
	/* wait for command completion */
	while (read_reg(info, (unsigned char)(channel+STAR)) & BIT2) {
		udelay(1);
		if (i++ == 1000)
			return false;
	}
	return true;
}