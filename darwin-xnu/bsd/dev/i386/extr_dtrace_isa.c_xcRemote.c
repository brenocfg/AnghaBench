#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ cpu; int /*<<< orphan*/  arg; int /*<<< orphan*/  (* f ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ xcArg_t ;
struct TYPE_4__ {scalar_t__ cpu_id; } ;

/* Variables and functions */
 TYPE_2__* CPU ; 
 scalar_t__ DTRACE_CPUALL ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xcRemote( void *foo )
{
	xcArg_t *pArg = (xcArg_t *)foo;
	
	if ( pArg->cpu == CPU->cpu_id || pArg->cpu == DTRACE_CPUALL ) {
		(pArg->f)(pArg->arg);
	}
}