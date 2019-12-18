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
typedef  int* vec3_t ;
struct TYPE_2__ {int (* DebugLineCreate ) () ;int /*<<< orphan*/  (* DebugLineShow ) (int,int*,int*,int) ;} ;

/* Variables and functions */
 int MAX_DEBUGLINES ; 
 int /*<<< orphan*/  VectorCopy (int*,int*) ; 
 TYPE_1__ botimport ; 
 int* debuglines ; 
 scalar_t__* debuglinevisible ; 
 int /*<<< orphan*/  numdebuglines ; 
 scalar_t__ qtrue ; 
 int stub1 () ; 
 int /*<<< orphan*/  stub2 (int,int*,int*,int) ; 
 int /*<<< orphan*/  stub3 (int,int*,int*,int) ; 

void AAS_DrawPlaneCross(vec3_t point, vec3_t normal, float dist, int type, int color)
{
	int n0, n1, n2, j, line, lines[2];
	vec3_t start1, end1, start2, end2;

	//make a cross in the hit plane at the hit point
	VectorCopy(point, start1);
	VectorCopy(point, end1);
	VectorCopy(point, start2);
	VectorCopy(point, end2);

	n0 = type % 3;
	n1 = (type + 1) % 3;
	n2 = (type + 2) % 3;
	start1[n1] -= 6;
	start1[n2] -= 6;
	end1[n1] += 6;
	end1[n2] += 6;
	start2[n1] += 6;
	start2[n2] -= 6;
	end2[n1] -= 6;
	end2[n2] += 6;

	start1[n0] = (dist - (start1[n1] * normal[n1] +
				start1[n2] * normal[n2])) / normal[n0];
	end1[n0] = (dist - (end1[n1] * normal[n1] +
				end1[n2] * normal[n2])) / normal[n0];
	start2[n0] = (dist - (start2[n1] * normal[n1] +
				start2[n2] * normal[n2])) / normal[n0];
	end2[n0] = (dist - (end2[n1] * normal[n1] +
				end2[n2] * normal[n2])) / normal[n0];

	for (j = 0, line = 0; j < 2 && line < MAX_DEBUGLINES; line++)
	{
		if (!debuglines[line])
		{
			debuglines[line] = botimport.DebugLineCreate();
			lines[j++] = debuglines[line];
			debuglinevisible[line] = qtrue;
			numdebuglines++;
		} //end if
		else if (!debuglinevisible[line])
		{
			lines[j++] = debuglines[line];
			debuglinevisible[line] = qtrue;
		} //end else
	} //end for
	botimport.DebugLineShow(lines[0], start1, end1, color);
	botimport.DebugLineShow(lines[1], start2, end2, color);
}