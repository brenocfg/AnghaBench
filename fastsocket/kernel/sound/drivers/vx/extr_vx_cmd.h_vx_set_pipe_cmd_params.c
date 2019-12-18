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
typedef  int u32 ;
struct vx_rmh {int* Cmd; } ;

/* Variables and functions */
 int COMMAND_RECORD_MASK ; 
 int FIELD_SIZE ; 
 int MASK_DSP_WORD ; 
 int MASK_FIRST_FIELD ; 

__attribute__((used)) static inline void vx_set_pipe_cmd_params(struct vx_rmh *rmh, int is_capture,
					  int param1, int param2)
{
	if (is_capture)
		rmh->Cmd[0] |= COMMAND_RECORD_MASK;
	rmh->Cmd[0] |= (((u32)param1 & MASK_FIRST_FIELD) << FIELD_SIZE) & MASK_DSP_WORD;
		
	if (param2)
		rmh->Cmd[0] |= ((u32)param2 & MASK_FIRST_FIELD) & MASK_DSP_WORD;
	
}