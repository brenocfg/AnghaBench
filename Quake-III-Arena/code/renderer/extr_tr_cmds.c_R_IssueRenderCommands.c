#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ cmds; scalar_t__ used; } ;
typedef  TYPE_1__ renderCommandList_t ;
typedef  scalar_t__ qboolean ;
struct TYPE_16__ {TYPE_1__ commands; } ;
struct TYPE_15__ {scalar_t__ smpActive; } ;
struct TYPE_14__ {scalar_t__ integer; } ;
struct TYPE_13__ {int /*<<< orphan*/  integer; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* Printf ) (int /*<<< orphan*/ ,char*) ;} ;
struct TYPE_11__ {size_t smpFrame; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLimp_FrontEndSleep () ; 
 int /*<<< orphan*/  GLimp_WakeRenderer (TYPE_1__*) ; 
 int /*<<< orphan*/  PRINT_ALL ; 
 int /*<<< orphan*/  RB_ExecuteRenderCommands (scalar_t__) ; 
 int RC_END_OF_LIST ; 
 int /*<<< orphan*/  R_PerformanceCounters () ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 TYPE_7__** backEndData ; 
 int /*<<< orphan*/  c_blockedOnMain ; 
 int /*<<< orphan*/  c_blockedOnRender ; 
 TYPE_6__ glConfig ; 
 TYPE_5__* r_showSmp ; 
 TYPE_4__* r_skipBackEnd ; 
 scalar_t__ renderThreadActive ; 
 TYPE_3__ ri ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__ tr ; 

void R_IssueRenderCommands( qboolean runPerformanceCounters ) {
	renderCommandList_t	*cmdList;

	cmdList = &backEndData[tr.smpFrame]->commands;
	assert(cmdList); // bk001205
	// add an end-of-list command
	*(int *)(cmdList->cmds + cmdList->used) = RC_END_OF_LIST;

	// clear it out, in case this is a sync and not a buffer flip
	cmdList->used = 0;

	if ( glConfig.smpActive ) {
		// if the render thread is not idle, wait for it
		if ( renderThreadActive ) {
			c_blockedOnRender++;
			if ( r_showSmp->integer ) {
				ri.Printf( PRINT_ALL, "R" );
			}
		} else {
			c_blockedOnMain++;
			if ( r_showSmp->integer ) {
				ri.Printf( PRINT_ALL, "." );
			}
		}

		// sleep until the renderer has completed
		GLimp_FrontEndSleep();
	}

	// at this point, the back end thread is idle, so it is ok
	// to look at it's performance counters
	if ( runPerformanceCounters ) {
		R_PerformanceCounters();
	}

	// actually start the commands going
	if ( !r_skipBackEnd->integer ) {
		// let it start on the new batch
		if ( !glConfig.smpActive ) {
			RB_ExecuteRenderCommands( cmdList->cmds );
		} else {
			GLimp_WakeRenderer( cmdList );
		}
	}
}