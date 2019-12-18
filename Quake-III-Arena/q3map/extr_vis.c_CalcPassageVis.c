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

/* Variables and functions */
 int /*<<< orphan*/  CreatePassages ; 
 int /*<<< orphan*/  PassageFlow ; 
 int /*<<< orphan*/  PassageMemory () ; 
 int /*<<< orphan*/  RunThreadsOnIndividual (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _printf (char*,...) ; 
 int numportals ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

void CalcPassageVis(void)
{
	PassageMemory();

#ifdef MREDEBUG
	_printf("%6d portals out of %d", 0, numportals*2);
	RunThreadsOnIndividual (numportals*2, qfalse, CreatePassages);
	_printf("\n");
	_printf("%6d portals out of %d", 0, numportals*2);
	RunThreadsOnIndividual (numportals*2, qfalse, PassageFlow);
	_printf("\n");
#else
	RunThreadsOnIndividual (numportals*2, qtrue, CreatePassages);
	RunThreadsOnIndividual (numportals*2, qtrue, PassageFlow);
#endif
}