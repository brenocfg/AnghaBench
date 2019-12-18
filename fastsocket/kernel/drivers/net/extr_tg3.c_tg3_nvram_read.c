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
struct tg3 {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NVRAM ; 
 int /*<<< orphan*/  NVRAM_ADDR ; 
 int /*<<< orphan*/  NVRAM_ADDR_MSK ; 
 int NVRAM_CMD_DONE ; 
 int NVRAM_CMD_FIRST ; 
 int NVRAM_CMD_GO ; 
 int NVRAM_CMD_LAST ; 
 int NVRAM_CMD_RD ; 
 int /*<<< orphan*/  NVRAM_RDDATA ; 
 int /*<<< orphan*/  tg3_disable_nvram_access (struct tg3*) ; 
 int /*<<< orphan*/  tg3_enable_nvram_access (struct tg3*) ; 
 int /*<<< orphan*/  tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 int tg3_nvram_exec_cmd (struct tg3*,int) ; 
 int tg3_nvram_lock (struct tg3*) ; 
 int /*<<< orphan*/  tg3_nvram_phys_addr (struct tg3*,int /*<<< orphan*/ ) ; 
 int tg3_nvram_read_using_eeprom (struct tg3*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tg3_nvram_unlock (struct tg3*) ; 
 int /*<<< orphan*/  tr32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tg3_nvram_read(struct tg3 *tp, u32 offset, u32 *val)
{
	int ret;

	if (!tg3_flag(tp, NVRAM))
		return tg3_nvram_read_using_eeprom(tp, offset, val);

	offset = tg3_nvram_phys_addr(tp, offset);

	if (offset > NVRAM_ADDR_MSK)
		return -EINVAL;

	ret = tg3_nvram_lock(tp);
	if (ret)
		return ret;

	tg3_enable_nvram_access(tp);

	tw32(NVRAM_ADDR, offset);
	ret = tg3_nvram_exec_cmd(tp, NVRAM_CMD_RD | NVRAM_CMD_GO |
		NVRAM_CMD_FIRST | NVRAM_CMD_LAST | NVRAM_CMD_DONE);

	if (ret == 0)
		*val = tr32(NVRAM_RDDATA);

	tg3_disable_nvram_access(tp);

	tg3_nvram_unlock(tp);

	return ret;
}