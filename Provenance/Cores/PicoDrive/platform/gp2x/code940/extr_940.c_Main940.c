#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int lastjob; int* writebuff0; int* writebuff1; int /*<<< orphan*/  loopc; int /*<<< orphan*/  rate; int /*<<< orphan*/  baseclock; } ;
struct TYPE_4__ {int* REGS; } ;
struct TYPE_5__ {int* ym_buffer; void* mp3dec; TYPE_1__ ym2612; } ;

/* Variables and functions */
#define  JOB940_INITALL 137 
#define  JOB940_INVALIDATE_DCACHE 136 
#define  JOB940_MP3DECODE 135 
#define  JOB940_MP3RESET 134 
#define  JOB940_PICOSTATELOAD 133 
#define  JOB940_PICOSTATELOAD2 132 
#define  JOB940_PICOSTATELOAD2_PREP 131 
#define  JOB940_PICOSTATESAVE2 130 
#define  JOB940_YM2612RESETCHIP 129 
#define  JOB940_YM2612UPDATEONE 128 
 int /*<<< orphan*/  MP3FreeDecoder (void*) ; 
 void* MP3InitDecoder () ; 
 int /*<<< orphan*/  YM2612Init_ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  YM2612PicoStateLoad2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  YM2612PicoStateLoad_ () ; 
 int /*<<< orphan*/  YM2612PicoStateSave2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  YM2612ResetChip_ () ; 
 int /*<<< orphan*/  _memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  dcache_clean () ; 
 int /*<<< orphan*/  dcache_clean_flush () ; 
 int /*<<< orphan*/  drain_wb () ; 
 int /*<<< orphan*/  mp3_decode () ; 
 TYPE_3__* shared_ctl ; 
 TYPE_2__* shared_data ; 
 int wait_get_job (int) ; 
 TYPE_1__* ym2612_940 ; 
 int /*<<< orphan*/  ym_flush_writes () ; 
 int /*<<< orphan*/  ym_update (int*) ; 

void Main940(void)
{
	int *ym_buffer = shared_data->ym_buffer;
	int job = 0;
	ym2612_940 = &shared_data->ym2612;


	for (;;)
	{
		job = wait_get_job(job);

		shared_ctl->lastjob = job;

		switch (job)
		{
			case JOB940_INITALL:
				/* ym2612 */
				shared_ctl->writebuff0[0] = shared_ctl->writebuff1[0] = 0xffff;
				YM2612Init_(shared_ctl->baseclock, shared_ctl->rate);
				/* Helix mp3 decoder */
				shared_data->mp3dec = MP3InitDecoder();
				break;

			case JOB940_INVALIDATE_DCACHE:
				drain_wb();
				dcache_clean_flush();
				break;

			case JOB940_YM2612RESETCHIP:
				YM2612ResetChip_();
				break;

			case JOB940_PICOSTATELOAD:
				YM2612PicoStateLoad_();
				break;

			case JOB940_PICOSTATESAVE2:
				YM2612PicoStateSave2(0, 0);
				_memcpy(shared_ctl->writebuff0, ym2612_940->REGS, 0x200);
				break;

			case JOB940_PICOSTATELOAD2_PREP:
				ym_flush_writes();
				break;

			case JOB940_PICOSTATELOAD2:
				_memcpy(ym2612_940->REGS, shared_ctl->writebuff0, 0x200);
				YM2612PicoStateLoad2(0, 0);
				break;

			case JOB940_YM2612UPDATEONE:
				ym_update(ym_buffer);
				break;

			case JOB940_MP3DECODE:
				mp3_decode();
				break;

			case JOB940_MP3RESET:
				if (shared_data->mp3dec) MP3FreeDecoder(shared_data->mp3dec);
				shared_data->mp3dec = MP3InitDecoder();
				break;
		}

		shared_ctl->loopc++;
		dcache_clean();
	}
}