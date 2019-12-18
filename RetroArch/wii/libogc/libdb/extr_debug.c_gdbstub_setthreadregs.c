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
typedef  int s32 ;
typedef  int /*<<< orphan*/  frame_context ;

/* Variables and functions */

__attribute__((used)) static s32 gdbstub_setthreadregs(s32 thread,frame_context *frame)
{
	return 1;
}