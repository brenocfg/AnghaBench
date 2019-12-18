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
struct TYPE_7__ {int /*<<< orphan*/  hModel; int /*<<< orphan*/  axis; int /*<<< orphan*/  origin; } ;
typedef  TYPE_2__ refEntity_t ;
typedef  int /*<<< orphan*/  qhandle_t ;
struct TYPE_6__ {scalar_t__ trTime; int /*<<< orphan*/  trDelta; int /*<<< orphan*/  trBase; int /*<<< orphan*/  trType; } ;
struct TYPE_8__ {float bounceFactor; int /*<<< orphan*/  leMarkType; int /*<<< orphan*/  leBounceSoundType; TYPE_1__ pos; scalar_t__ startTime; scalar_t__ endTime; int /*<<< orphan*/  leType; TYPE_2__ refEntity; } ;
typedef  TYPE_3__ localEntity_t ;
struct TYPE_9__ {scalar_t__ time; } ;

/* Variables and functions */
 int /*<<< orphan*/  AxisCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* CG_AllocLocalEntity () ; 
 int /*<<< orphan*/  LEBS_BRASS ; 
 int /*<<< orphan*/  LEMT_NONE ; 
 int /*<<< orphan*/  LE_FRAGMENT ; 
 int /*<<< orphan*/  TR_GRAVITY ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  axisDefault ; 
 TYPE_4__ cg ; 
 int random () ; 

void CG_LaunchExplode( vec3_t origin, vec3_t velocity, qhandle_t hModel ) {
	localEntity_t	*le;
	refEntity_t		*re;

	le = CG_AllocLocalEntity();
	re = &le->refEntity;

	le->leType = LE_FRAGMENT;
	le->startTime = cg.time;
	le->endTime = le->startTime + 10000 + random() * 6000;

	VectorCopy( origin, re->origin );
	AxisCopy( axisDefault, re->axis );
	re->hModel = hModel;

	le->pos.trType = TR_GRAVITY;
	VectorCopy( origin, le->pos.trBase );
	VectorCopy( velocity, le->pos.trDelta );
	le->pos.trTime = cg.time;

	le->bounceFactor = 0.1f;

	le->leBounceSoundType = LEBS_BRASS;
	le->leMarkType = LEMT_NONE;
}