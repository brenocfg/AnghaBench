#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int faceflags; } ;
typedef  TYPE_1__ aas_face_t ;

/* Variables and functions */
 int FACE_LADDER ; 

int AAS_KeepFace(aas_face_t *face)
{
	if (!(face->faceflags & FACE_LADDER)) return 0;
	else return 1;
}