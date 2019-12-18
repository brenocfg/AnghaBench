#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct carlu {int dummy; } ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  addr ;
struct TYPE_3__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  CARL9170_CMD_RREG ; 
 int carlusb_cmd (struct carlu*,int /*<<< orphan*/ ,void*,int,void*,int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  le32_to_cpu (TYPE_1__) ; 

int carlu_cmd_read_mem(struct carlu *ar, const uint32_t _addr,
		       uint32_t *val)
{
	int err;
	__le32 msg, addr = { cpu_to_le32(_addr) };
	err = carlusb_cmd(ar, CARL9170_CMD_RREG, (void *) &addr, sizeof(addr),
			  (void *) &msg, sizeof(msg));

	*val = le32_to_cpu(msg);
	return err;
}