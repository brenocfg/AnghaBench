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
typedef  int /*<<< orphan*/  uint32_t ;
struct carlu {int dummy; } ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  block ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  CARL9170_CMD_WREG ; 
 int carlusb_cmd (struct carlu*,int /*<<< orphan*/ ,void*,int,void*,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/  const) ; 

int carlu_cmd_write_mem(struct carlu *ar, const uint32_t addr,
			const uint32_t val)
{
	int err;
	__le32 msg, block[2] = { cpu_to_le32(addr), cpu_to_le32(val) };

	err = carlusb_cmd(ar, CARL9170_CMD_WREG,
			  (void *) &block, sizeof(block),
			  (void *) &msg, sizeof(msg));
	return err;
}