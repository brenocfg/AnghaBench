#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_3__ {int fraction; } ;
typedef  TYPE_1__ bsp_trace_t ;

/* Variables and functions */
 TYPE_1__ AAS_Trace (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int CONTENTS_PLAYERCLIP ; 
 int CONTENTS_SOLID ; 
 int qfalse ; 
 int qtrue ; 

int BotVisible(int ent, vec3_t eye, vec3_t target)
{
	bsp_trace_t trace;

	trace = AAS_Trace(eye, NULL, NULL, target, ent, CONTENTS_SOLID|CONTENTS_PLAYERCLIP);
	if (trace.fraction >= 1) return qtrue;
	return qfalse;
}