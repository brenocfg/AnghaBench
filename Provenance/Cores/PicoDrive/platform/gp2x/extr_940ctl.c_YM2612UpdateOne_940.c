#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ym_active_chs; int writebuffsel; int* writebuff0; int* writebuff1; int length; int stereo; } ;
struct TYPE_3__ {int* ym_buffer; } ;

/* Variables and functions */
 scalar_t__ CHECK_BUSY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JOB940_YM2612UPDATEONE ; 
 int PsndLen ; 
 int PsndLen_exc_add ; 
 int PsndLen_exc_cnt ; 
 int /*<<< orphan*/  add_job_940 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy32 (int*,int*,int) ; 
 int /*<<< orphan*/  memset32 (int*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* shared_ctl ; 
 TYPE_1__* shared_data ; 
 int /*<<< orphan*/  wait_busy_940 (int /*<<< orphan*/ ) ; 
 int writebuff_ptr ; 

int YM2612UpdateOne_940(int *buffer, int length, int stereo, int is_buf_empty)
{
	int *ym_buf = shared_data->ym_buffer;
	int ym_active_chs;

	//printf("YM2612UpdateOne_940()\n");

	if (CHECK_BUSY(JOB940_YM2612UPDATEONE)) wait_busy_940(JOB940_YM2612UPDATEONE);

	ym_active_chs = shared_ctl->ym_active_chs;

	// mix in ym buffer. is_buf_empty means nobody mixed there anything yet and it may contain trash
	if (is_buf_empty && ym_active_chs) memcpy32(buffer, ym_buf, length<<stereo);
	else memset32(buffer, 0, length<<stereo);

	if (shared_ctl->writebuffsel == 1) {
		shared_ctl->writebuff0[writebuff_ptr & 0xffff] = 0xffff;
	} else {
		shared_ctl->writebuff1[writebuff_ptr & 0xffff] = 0xffff;
	}
	writebuff_ptr = 0;

	/* predict sample counter for next frame */
	if (PsndLen_exc_add) {
		length = PsndLen;
		if (PsndLen_exc_cnt + PsndLen_exc_add >= 0x10000) length++;
	}

	/* give 940 ym job */
	shared_ctl->writebuffsel ^= 1;
	shared_ctl->length = length;
	shared_ctl->stereo = stereo;

	add_job_940(JOB940_YM2612UPDATEONE);

	return ym_active_chs;
}