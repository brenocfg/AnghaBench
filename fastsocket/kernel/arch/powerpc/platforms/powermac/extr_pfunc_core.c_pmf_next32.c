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
typedef  int /*<<< orphan*/  u32 ;
struct pmf_cmd {int cmdend; int cmdptr; int error; } ;

/* Variables and functions */

__attribute__((used)) static u32 pmf_next32(struct pmf_cmd *cmd)
{
	u32 value;
	if ((cmd->cmdend - cmd->cmdptr) < 4) {
		cmd->error = 1;
		return 0;
	}
	value = *((u32 *)cmd->cmdptr);
	cmd->cmdptr += 4;
	return value;
}