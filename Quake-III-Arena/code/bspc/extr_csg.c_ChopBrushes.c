#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {struct TYPE_21__* next; } ;
typedef  TYPE_1__ bspbrush_t ;

/* Variables and functions */
 TYPE_1__* AddBrushListToTail (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ BrushGE (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ BrushesDisjoint (TYPE_1__*,TYPE_1__*) ; 
 int CountBrushList (TYPE_1__*) ; 
 TYPE_1__* CullList (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  FreeBrushList (TYPE_1__*) ; 
 int /*<<< orphan*/  Log_Print (char*,...) ; 
 int /*<<< orphan*/  Log_Write (char*,int) ; 
 TYPE_1__* SubtractBrush (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  WriteBrushList (char*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  WriteBrushMap (char*,TYPE_1__*) ; 
 scalar_t__ cancelconversion ; 
 int /*<<< orphan*/  qprintf (char*,...) ; 
 scalar_t__ startbrush ; 

bspbrush_t *ChopBrushes (bspbrush_t *head)
{
	bspbrush_t	*b1, *b2, *next;
	bspbrush_t	*tail;
	bspbrush_t	*keep;
	bspbrush_t	*sub, *sub2;
	int			c1, c2;
	int num_csg_iterations;

	Log_Print("-------- Brush CSG ---------\n");
	Log_Print("%6d original brushes\n", CountBrushList (head));

	num_csg_iterations = 0;
	qprintf("%6d output brushes", num_csg_iterations);

#if 0
	if (startbrush == 0)
		WriteBrushList ("before.gl", head, false);
#endif
	keep = NULL;

newlist:
	// find tail
	if (!head) return NULL;

	for (tail = head; tail->next; tail = tail->next)
		;

	for (b1=head ; b1 ; b1=next)
	{
		next = b1->next;

		//if the conversion is cancelled
		if (cancelconversion)
		{
			b1->next = keep;
			keep = b1;
			continue;
		} //end if
		
		for (b2 = b1->next; b2; b2 = b2->next)
		{
			if (BrushesDisjoint (b1, b2))
				continue;

			sub = NULL;
			sub2 = NULL;
			c1 = 999999;
			c2 = 999999;

			if (BrushGE (b2, b1))
			{
				sub = SubtractBrush (b1, b2);
				if (sub == b1)
				{
					continue;		// didn't really intersect
				} //end if
				if (!sub)
				{	// b1 is swallowed by b2
					head = CullList (b1, b1);
					goto newlist;
				}
				c1 = CountBrushList (sub);
			}

			if ( BrushGE (b1, b2) )
			{
				sub2 = SubtractBrush (b2, b1);
				if (sub2 == b2)
					continue;		// didn't really intersect
				if (!sub2)
				{	// b2 is swallowed by b1
					FreeBrushList (sub);
					head = CullList (b1, b2);
					goto newlist;
				}
				c2 = CountBrushList (sub2);
			}

			if (!sub && !sub2)
				continue;		// neither one can bite

			// only accept if it didn't fragment
			// (commenting this out allows full fragmentation)
			if (c1 > 1 && c2 > 1)
			{
				if (sub2)
					FreeBrushList (sub2);
				if (sub)
					FreeBrushList (sub);
				continue;
			}

			if (c1 < c2)
			{
				if (sub2) FreeBrushList (sub2);
				tail = AddBrushListToTail (sub, tail);
				head = CullList (b1, b1);
				goto newlist;
			} //end if
			else
			{
				if (sub) FreeBrushList (sub);
				tail = AddBrushListToTail (sub2, tail);
				head = CullList (b1, b2);
				goto newlist;
			} //end else
		} //end for

		if (!b2)
		{	// b1 is no longer intersecting anything, so keep it
			b1->next = keep;
			keep = b1;
		} //end if
		num_csg_iterations++;
		qprintf("\r%6d", num_csg_iterations);
	} //end for

	if (cancelconversion) return keep;
	//
	qprintf("\n");
	Log_Write("%6d output brushes\r\n", num_csg_iterations);

#if 0
	{
		WriteBrushList ("after.gl", keep, false);
		WriteBrushMap ("after.map", keep);
	}
#endif

	return keep;
}