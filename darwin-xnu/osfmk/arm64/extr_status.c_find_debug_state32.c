#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_4__* thread_t ;
typedef  int /*<<< orphan*/  arm_debug_state32_t ;
struct TYPE_8__ {TYPE_2__* DebugData; } ;
struct TYPE_9__ {TYPE_3__ machine; } ;
struct TYPE_6__ {int /*<<< orphan*/  ds32; } ;
struct TYPE_7__ {TYPE_1__ uds; } ;

/* Variables and functions */

arm_debug_state32_t *
find_debug_state32(
             thread_t thread)
{
	if (thread && thread->machine.DebugData)
		return &(thread->machine.DebugData->uds.ds32);
	else
		return NULL;
}