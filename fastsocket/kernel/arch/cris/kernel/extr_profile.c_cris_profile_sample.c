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
struct pt_regs {int dummy; } ;
struct TYPE_2__ {unsigned int pid; } ;

/* Variables and functions */
 scalar_t__ SAMPLE_BUFFER_SIZE ; 
 TYPE_1__* current ; 
 unsigned int instruction_pointer (struct pt_regs*) ; 
 int /*<<< orphan*/  prof_running ; 
 scalar_t__ sample_buffer ; 
 scalar_t__ sample_buffer_pos ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

void
cris_profile_sample(struct pt_regs* regs)
{
	if (!prof_running)
		return;

	if (user_mode(regs))
		*(unsigned int*)sample_buffer_pos = current->pid;
	else
		*(unsigned int*)sample_buffer_pos = 0;

	*(unsigned int*)(sample_buffer_pos + 4) = instruction_pointer(regs);
	sample_buffer_pos += 8;

	if (sample_buffer_pos == sample_buffer + SAMPLE_BUFFER_SIZE)
		sample_buffer_pos = sample_buffer;
}