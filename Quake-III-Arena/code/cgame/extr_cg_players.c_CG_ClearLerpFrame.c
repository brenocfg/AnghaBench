#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* animation; int /*<<< orphan*/  frame; int /*<<< orphan*/  oldFrame; int /*<<< orphan*/  oldFrameTime; int /*<<< orphan*/  frameTime; } ;
typedef  TYPE_2__ lerpFrame_t ;
typedef  int /*<<< orphan*/  clientInfo_t ;
struct TYPE_8__ {int /*<<< orphan*/  time; } ;
struct TYPE_6__ {int /*<<< orphan*/  firstFrame; } ;

/* Variables and functions */
 int /*<<< orphan*/  CG_SetLerpFrameAnimation (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 TYPE_3__ cg ; 

__attribute__((used)) static void CG_ClearLerpFrame( clientInfo_t *ci, lerpFrame_t *lf, int animationNumber ) {
	lf->frameTime = lf->oldFrameTime = cg.time;
	CG_SetLerpFrameAnimation( ci, lf, animationNumber );
	lf->oldFrame = lf->frame = lf->animation->firstFrame;
}