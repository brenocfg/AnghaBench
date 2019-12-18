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
 int /*<<< orphan*/  r_firstSceneDlight ; 
 int /*<<< orphan*/  r_firstSceneEntity ; 
 int /*<<< orphan*/  r_firstScenePoly ; 
 int /*<<< orphan*/  r_numdlights ; 
 int /*<<< orphan*/  r_numentities ; 
 int /*<<< orphan*/  r_numpolys ; 

void RE_ClearScene( void ) {
	r_firstSceneDlight = r_numdlights;
	r_firstSceneEntity = r_numentities;
	r_firstScenePoly = r_numpolys;
}