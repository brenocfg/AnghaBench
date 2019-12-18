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
struct TYPE_2__ {scalar_t__ esp0; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
 unsigned short EXR_TRACE ; 
 size_t PT_EXR ; 
 scalar_t__* h8300_register_offset ; 

void h8300_enable_trace(struct task_struct *child)
{
	*(unsigned short *)(child->thread.esp0 + h8300_register_offset[PT_EXR]) |= EXR_TRACE;
}