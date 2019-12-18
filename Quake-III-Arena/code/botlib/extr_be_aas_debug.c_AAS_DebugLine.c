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
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* DebugLineShow ) (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;scalar_t__ (* DebugLineCreate ) () ;} ;

/* Variables and functions */
 int MAX_DEBUGLINES ; 
 TYPE_1__ botimport ; 
 scalar_t__* debuglines ; 
 scalar_t__* debuglinevisible ; 
 int /*<<< orphan*/  numdebuglines ; 
 scalar_t__ qfalse ; 
 scalar_t__ qtrue ; 
 scalar_t__ stub1 () ; 
 int /*<<< orphan*/  stub2 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void AAS_DebugLine(vec3_t start, vec3_t end, int color)
{
	int line;

	for (line = 0; line < MAX_DEBUGLINES; line++)
	{
		if (!debuglines[line])
		{
			debuglines[line] = botimport.DebugLineCreate();
			debuglinevisible[line] = qfalse;
			numdebuglines++;
		} //end if
		if (!debuglinevisible[line])
		{
			botimport.DebugLineShow(debuglines[line], start, end, color);
			debuglinevisible[line] = qtrue;
			return;
		} //end else
	} //end for
}