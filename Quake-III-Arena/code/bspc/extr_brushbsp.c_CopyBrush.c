#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t numsides; TYPE_1__* sides; } ;
typedef  TYPE_2__ bspbrush_t ;
struct TYPE_8__ {scalar_t__ winding; } ;

/* Variables and functions */
 TYPE_2__* AllocBrush (size_t) ; 
 scalar_t__ CopyWinding (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 

bspbrush_t *CopyBrush (bspbrush_t *brush)
{
	bspbrush_t *newbrush;
	int			size;
	int			i;
	
	size = (int)&(((bspbrush_t *)0)->sides[brush->numsides]);

	newbrush = AllocBrush (brush->numsides);
	memcpy (newbrush, brush, size);

	for (i=0 ; i<brush->numsides ; i++)
	{
		if (brush->sides[i].winding)
			newbrush->sides[i].winding = CopyWinding (brush->sides[i].winding);
	}

	return newbrush;
}