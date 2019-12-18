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
typedef  int /*<<< orphan*/  glconfig_t ;
struct TYPE_2__ {int viewCluster; int /*<<< orphan*/  registered; } ;

/* Variables and functions */
 int /*<<< orphan*/  RE_ClearScene () ; 
 int /*<<< orphan*/  RE_StretchPic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_ClearFlares () ; 
 int /*<<< orphan*/  R_Init () ; 
 int /*<<< orphan*/  R_SyncRenderThread () ; 
 int /*<<< orphan*/  glConfig ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_1__ tr ; 

void RE_BeginRegistration( glconfig_t *glconfigOut ) {

	R_Init();

	*glconfigOut = glConfig;

	R_SyncRenderThread();

	tr.viewCluster = -1;		// force markleafs to regenerate
	R_ClearFlares();
	RE_ClearScene();

	tr.registered = qtrue;

	// NOTE: this sucks, for some reason the first stretch pic is never drawn
	// without this we'd see a white flash on a level load because the very
	// first time the level shot would not be drawn
	RE_StretchPic(0, 0, 0, 0, 0, 0, 1, 1, 0);
}