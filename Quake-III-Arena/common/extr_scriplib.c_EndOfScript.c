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
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_3__ {char* filename; int /*<<< orphan*/  line; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetToken (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  endofscript ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_1__* script ; 
 int /*<<< orphan*/  scriptline ; 
 TYPE_1__* scriptstack ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

qboolean EndOfScript (qboolean crossline)
{
	if (!crossline)
		Error ("Line %i is incomplete\n",scriptline);

	if (!strcmp (script->filename, "memory buffer"))
	{
		endofscript = qtrue;
		return qfalse;
	}

	free (script->buffer);
	if (script == scriptstack+1)
	{
		endofscript = qtrue;
		return qfalse;
	}
	script--;
	scriptline = script->line;
	printf ("returning to %s\n", script->filename);
	return GetToken (crossline);
}