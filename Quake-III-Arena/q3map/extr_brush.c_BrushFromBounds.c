#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int vec_t ;
typedef  int* vec3_t ;
struct TYPE_7__ {int numsides; TYPE_1__* sides; } ;
typedef  TYPE_2__ bspbrush_t ;
struct TYPE_6__ {void* planenum; } ;

/* Variables and functions */
 TYPE_2__* AllocBrush (int) ; 
 int /*<<< orphan*/  CreateBrushWindings (TYPE_2__*) ; 
 void* FindFloatPlane (int*,int) ; 
 int /*<<< orphan*/  VectorClear (int*) ; 

bspbrush_t	*BrushFromBounds (vec3_t mins, vec3_t maxs)
{
	bspbrush_t	*b;
	int			i;
	vec3_t		normal;
	vec_t		dist;

	b = AllocBrush (6);
	b->numsides = 6;
	for (i=0 ; i<3 ; i++)
	{
		VectorClear (normal);
		normal[i] = 1;
		dist = maxs[i];
		b->sides[i].planenum = FindFloatPlane (normal, dist);

		normal[i] = -1;
		dist = -mins[i];
		b->sides[3+i].planenum = FindFloatPlane (normal, dist);
	}

	CreateBrushWindings (b);

	return b;
}