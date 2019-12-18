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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct megasas_sge_skinny {int dummy; } ;
struct megasas_sge64 {int dummy; } ;
struct megasas_sge32 {int dummy; } ;
struct megasas_instance {int flag_ieee; } ;

/* Variables and functions */
 scalar_t__ IS_DMA64 ; 
 int MEGAMFI_FRAME_SIZE ; 
 scalar_t__ PTHRU_FRAME ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u32 megasas_get_frame_count(struct megasas_instance *instance,
			u8 sge_count, u8 frame_type)
{
	int num_cnt;
	int sge_bytes;
	u32 sge_sz;
	u32 frame_count=0;

	sge_sz = (IS_DMA64) ? sizeof(struct megasas_sge64) :
	    sizeof(struct megasas_sge32);

	if (instance->flag_ieee) {
		sge_sz = sizeof(struct megasas_sge_skinny);
	}

	/*
	 * Main frame can contain 2 SGEs for 64-bit SGLs and
	 * 3 SGEs for 32-bit SGLs for ldio &
	 * 1 SGEs for 64-bit SGLs and
	 * 2 SGEs for 32-bit SGLs for pthru frame
	 */
	if (unlikely(frame_type == PTHRU_FRAME)) {
		if (instance->flag_ieee == 1) {
			num_cnt = sge_count - 1;
		} else if (IS_DMA64)
			num_cnt = sge_count - 1;
		else
			num_cnt = sge_count - 2;
	} else {
		if (instance->flag_ieee == 1) {
			num_cnt = sge_count - 1;
		} else if (IS_DMA64)
			num_cnt = sge_count - 2;
		else
			num_cnt = sge_count - 3;
	}

	if(num_cnt>0){
		sge_bytes = sge_sz * num_cnt;

		frame_count = (sge_bytes / MEGAMFI_FRAME_SIZE) +
		    ((sge_bytes % MEGAMFI_FRAME_SIZE) ? 1 : 0) ;
	}
	/* Main frame */
	frame_count +=1;

	if (frame_count > 7)
		frame_count = 8;
	return frame_count;
}