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
typedef  int /*<<< orphan*/  vortex_t ;

/* Variables and functions */
 int /*<<< orphan*/  asXtalkNarrowCoefsLeftEq ; 
 int /*<<< orphan*/  asXtalkNarrowCoefsLeftXt ; 
 int /*<<< orphan*/  asXtalkNarrowCoefsRightEq ; 
 int /*<<< orphan*/  sXtalkNarrowKLeftEq ; 
 int /*<<< orphan*/  sXtalkNarrowKLeftXt ; 
 int /*<<< orphan*/  sXtalkNarrowKRightEq ; 
 int /*<<< orphan*/  sXtalkNarrowShiftLeftEq ; 
 int /*<<< orphan*/  sXtalkNarrowShiftLeftXt ; 
 int /*<<< orphan*/  sXtalkNarrowShiftRightEq ; 
 int /*<<< orphan*/  vortex_XtalkHw_SetDelay (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_XtalkHw_SetLeftEQ (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_XtalkHw_SetLeftXT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_XtalkHw_SetRightEQ (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_XtalkHw_SetRightXT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wXtalkNarrowLeftDelay ; 
 int /*<<< orphan*/  wXtalkNarrowRightDelay ; 

__attribute__((used)) static void vortex_XtalkHw_ProgramXtalkNarrow(vortex_t * vortex)
{

	vortex_XtalkHw_SetLeftEQ(vortex, sXtalkNarrowKLeftEq,
				 sXtalkNarrowShiftLeftEq,
				 asXtalkNarrowCoefsLeftEq);
	vortex_XtalkHw_SetRightEQ(vortex, sXtalkNarrowKRightEq,
				  sXtalkNarrowShiftRightEq,
				  asXtalkNarrowCoefsRightEq);
	vortex_XtalkHw_SetLeftXT(vortex, sXtalkNarrowKLeftXt,
				 sXtalkNarrowShiftLeftXt,
				 asXtalkNarrowCoefsLeftXt);
	vortex_XtalkHw_SetRightXT(vortex, sXtalkNarrowKLeftXt,
				  sXtalkNarrowShiftLeftXt,
				  asXtalkNarrowCoefsLeftXt);

	vortex_XtalkHw_SetDelay(vortex, wXtalkNarrowRightDelay, wXtalkNarrowLeftDelay);	// inlined
}