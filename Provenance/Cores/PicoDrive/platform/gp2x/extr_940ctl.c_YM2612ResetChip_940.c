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

/* Variables and functions */
 int /*<<< orphan*/  JOB940_YM2612RESETCHIP ; 
 int /*<<< orphan*/  YM2612ResetChip_ () ; 
 int /*<<< orphan*/  add_job_940 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  internal_reset () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/ * shared_data ; 

void YM2612ResetChip_940(void)
{
	//printf("YM2612ResetChip_940()\n");
	if (shared_data == NULL) {
		printf("YM2612ResetChip_940: reset before init?\n");
		return;
	}

	YM2612ResetChip_();
	internal_reset();

	add_job_940(JOB940_YM2612RESETCHIP);
}