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
 int /*<<< orphan*/  asXtalkCoefsPipe ; 
 int /*<<< orphan*/  asXtalkCoefsZeros ; 
 int /*<<< orphan*/  vortex_XtalkHw_SetDelay (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_XtalkHw_SetLeftEQ (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_XtalkHw_SetLeftXT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_XtalkHw_SetRightEQ (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vortex_XtalkHw_SetRightXT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vortex_XtalkHw_ProgramPipe(vortex_t * vortex)
{

	vortex_XtalkHw_SetLeftEQ(vortex, 0, 1, asXtalkCoefsPipe);
	vortex_XtalkHw_SetRightEQ(vortex, 0, 1, asXtalkCoefsPipe);
	vortex_XtalkHw_SetLeftXT(vortex, 0, 0, asXtalkCoefsZeros);
	vortex_XtalkHw_SetRightXT(vortex, 0, 0, asXtalkCoefsZeros);

	vortex_XtalkHw_SetDelay(vortex, 0, 0);	// inlined
}