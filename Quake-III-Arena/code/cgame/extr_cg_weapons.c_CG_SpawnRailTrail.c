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
typedef  int /*<<< orphan*/  vec3_t ;
typedef  int /*<<< orphan*/  clientInfo_t ;
struct TYPE_7__ {int /*<<< orphan*/  railgunImpact; scalar_t__ railgunFlash; } ;
struct TYPE_6__ {scalar_t__ weapon; size_t clientNum; } ;
struct TYPE_8__ {TYPE_2__ pe; TYPE_1__ currentState; } ;
typedef  TYPE_3__ centity_t ;
struct TYPE_9__ {int /*<<< orphan*/ * clientinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_RailTrail (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ WP_RAILGUN ; 
 TYPE_4__ cgs ; 
 scalar_t__ qtrue ; 

__attribute__((used)) static void CG_SpawnRailTrail( centity_t *cent, vec3_t origin ) {
	clientInfo_t	*ci;

	if ( cent->currentState.weapon != WP_RAILGUN ) {
		return;
	}
	if ( !cent->pe.railgunFlash ) {
		return;
	}
	cent->pe.railgunFlash = qtrue;
	ci = &cgs.clientinfo[ cent->currentState.clientNum ];
	CG_RailTrail( ci, origin, cent->pe.railgunImpact );
}