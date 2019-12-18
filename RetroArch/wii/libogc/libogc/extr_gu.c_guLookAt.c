#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int x; int y; int z; } ;
typedef  TYPE_1__ guVector ;
typedef  int** Mtx ;

/* Variables and functions */
 int /*<<< orphan*/  guVecCross (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  guVecNormalize (TYPE_1__*) ; 

void guLookAt(Mtx mt,guVector *camPos,guVector *camUp,guVector *target)
{
	guVector vLook,vRight,vUp;

	vLook.x = camPos->x - target->x;
	vLook.y = camPos->y - target->y;
	vLook.z = camPos->z - target->z;
	guVecNormalize(&vLook);

	guVecCross(camUp,&vLook,&vRight);
	guVecNormalize(&vRight);

	guVecCross(&vLook,&vRight,&vUp);

    mt[0][0] = vRight.x;
    mt[0][1] = vRight.y;
    mt[0][2] = vRight.z;
    mt[0][3] = -( camPos->x * vRight.x + camPos->y * vRight.y + camPos->z * vRight.z );

    mt[1][0] = vUp.x;
    mt[1][1] = vUp.y;
    mt[1][2] = vUp.z;
    mt[1][3] = -( camPos->x * vUp.x + camPos->y * vUp.y + camPos->z * vUp.z );

    mt[2][0] = vLook.x;
    mt[2][1] = vLook.y;
    mt[2][2] = vLook.z;
    mt[2][3] = -( camPos->x * vLook.x + camPos->y * vLook.y + camPos->z * vLook.z );
}