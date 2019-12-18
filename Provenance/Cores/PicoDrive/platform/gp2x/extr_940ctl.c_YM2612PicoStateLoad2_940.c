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
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int UINT32 ;
struct TYPE_2__ {int* writebuff0; int writebuffsel; int* writebuff1; } ;
typedef  int INT32 ;

/* Variables and functions */
 scalar_t__ CHECK_BUSY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JOB940_PICOSTATELOAD2 ; 
 int /*<<< orphan*/  JOB940_PICOSTATELOAD2_PREP ; 
 int /*<<< orphan*/  JOB940_YM2612UPDATEONE ; 
 int /*<<< orphan*/ * YM2612GetRegs () ; 
 int /*<<< orphan*/  add_job_940 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* shared_ctl ; 
 int /*<<< orphan*/  wait_busy_940 (int /*<<< orphan*/ ) ; 
 int writebuff_ptr ; 

int YM2612PicoStateLoad2_940(int *tat, int *tbt)
{
	UINT8 *ym_remote_regs, *ym_local_regs;
	ym_local_regs  = YM2612GetRegs();
	ym_remote_regs = (UINT8 *) shared_ctl->writebuff0;

	if (*(UINT32 *)(ym_local_regs + 0x100) != 0x41534d59)
		return -1;

	*tat = *(INT32 *)(ym_local_regs + 0x108);
	*tbt = *(INT32 *)(ym_local_regs + 0x10c);

	if (CHECK_BUSY(JOB940_YM2612UPDATEONE)) wait_busy_940(JOB940_YM2612UPDATEONE);

	/* flush writes */
	if (shared_ctl->writebuffsel == 1) {
		shared_ctl->writebuff0[writebuff_ptr & 0xffff] = 0xffff;
	} else {
		shared_ctl->writebuff1[writebuff_ptr & 0xffff] = 0xffff;
	}
	shared_ctl->writebuffsel ^= 1;
	writebuff_ptr = 0;
	add_job_940(JOB940_PICOSTATELOAD2_PREP);
	if (CHECK_BUSY(JOB940_PICOSTATELOAD2_PREP)) wait_busy_940(JOB940_PICOSTATELOAD2_PREP);

	memcpy(ym_remote_regs, ym_local_regs, 0x200);

	add_job_940(JOB940_PICOSTATELOAD2);
	if (CHECK_BUSY(JOB940_PICOSTATELOAD2)) wait_busy_940(JOB940_PICOSTATELOAD2);

	return 0;
}