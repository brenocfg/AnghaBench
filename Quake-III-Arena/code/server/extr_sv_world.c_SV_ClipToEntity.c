#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vec3_t ;
struct TYPE_12__ {double fraction; int /*<<< orphan*/  entityNum; } ;
typedef  TYPE_3__ trace_t ;
struct TYPE_11__ {int /*<<< orphan*/  number; } ;
struct TYPE_10__ {int contents; float* currentOrigin; float* currentAngles; int /*<<< orphan*/  bmodel; } ;
struct TYPE_13__ {TYPE_2__ s; TYPE_1__ r; } ;
typedef  TYPE_4__ sharedEntity_t ;
typedef  int /*<<< orphan*/  clipHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  CM_TransformedBoxTrace (TYPE_3__*,float*,float*,float*,float*,int /*<<< orphan*/ ,int,float*,float*,int) ; 
 int /*<<< orphan*/  Com_Memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SV_ClipHandleForEntity (TYPE_4__*) ; 
 TYPE_4__* SV_GentityNum (int) ; 
 float* vec3_origin ; 

void SV_ClipToEntity( trace_t *trace, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int entityNum, int contentmask, int capsule ) {
	sharedEntity_t	*touch;
	clipHandle_t	clipHandle;
	float			*origin, *angles;

	touch = SV_GentityNum( entityNum );

	Com_Memset(trace, 0, sizeof(trace_t));

	// if it doesn't have any brushes of a type we
	// are looking for, ignore it
	if ( ! ( contentmask & touch->r.contents ) ) {
		trace->fraction = 1.0;
		return;
	}

	// might intersect, so do an exact clip
	clipHandle = SV_ClipHandleForEntity (touch);

	origin = touch->r.currentOrigin;
	angles = touch->r.currentAngles;

	if ( !touch->r.bmodel ) {
		angles = vec3_origin;	// boxes don't rotate
	}

	CM_TransformedBoxTrace ( trace, (float *)start, (float *)end,
		(float *)mins, (float *)maxs, clipHandle,  contentmask,
		origin, angles, capsule);

	if ( trace->fraction < 1 ) {
		trace->entityNum = touch->s.number;
	}
}