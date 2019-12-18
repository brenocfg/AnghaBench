#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {float dist; int /*<<< orphan*/  normal; } ;
struct TYPE_21__ {size_t leaf; scalar_t__ status; float radius; TYPE_2__ plane; void* winding; int /*<<< orphan*/  origin; scalar_t__ portalflood; scalar_t__ portalvis; scalar_t__ removed; TYPE_8__* passages; } ;
typedef  TYPE_4__ vportal_t ;
struct TYPE_24__ {float dist; int /*<<< orphan*/  normal; } ;
struct TYPE_18__ {TYPE_7__ portalplane; } ;
struct TYPE_22__ {TYPE_3__* base; TYPE_1__ pstack_head; } ;
typedef  TYPE_5__ threaddata_t ;
struct TYPE_23__ {int* numseperators; int* mightsee; int* freewindings; struct TYPE_23__* next; void* pass; void* source; TYPE_7__** seperators; TYPE_4__* portal; TYPE_2__ portalplane; scalar_t__ depth; TYPE_9__* leaf; } ;
typedef  TYPE_6__ pstack_t ;
typedef  TYPE_7__ plane_t ;
struct TYPE_25__ {scalar_t__ cansee; struct TYPE_25__* next; } ;
typedef  TYPE_8__ passage_t ;
struct TYPE_26__ {int numportals; TYPE_4__** portals; } ;
typedef  TYPE_9__ leaf_t ;
struct TYPE_20__ {int* portalvis; float radius; int /*<<< orphan*/  origin; } ;

/* Variables and functions */
 void* ClipToSeperators (void*,void*,void*,int /*<<< orphan*/ ,TYPE_6__*) ; 
 float DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* VisChopWinding (void*,TYPE_6__*,TYPE_7__*) ; 
 TYPE_9__* leafs ; 
 int /*<<< orphan*/  memcpy (long*,long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portalbytes ; 
 int portallongs ; 
 TYPE_4__* portals ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 scalar_t__ stat_done ; 
 int /*<<< orphan*/  vec3_origin ; 

void RecursivePassagePortalFlow (vportal_t *portal, threaddata_t *thread, pstack_t *prevstack)
{
	pstack_t	stack;
	vportal_t	*p;
	leaf_t 		*leaf;
	plane_t		backplane;
	passage_t	*passage, *nextpassage;
	int			i, j, n;
	long		*might, *vis, *prevmight, *cansee, *portalvis, more;
	int			pnum;

//	thread->c_chains++;

	leaf = &leafs[portal->leaf];
//	CheckStack (leaf, thread);

	prevstack->next = &stack;

	stack.next = NULL;
	stack.leaf = leaf;
	stack.portal = NULL;
	stack.depth = prevstack->depth + 1;

#ifdef SEPERATORCACHE
	stack.numseperators[0] = 0;
	stack.numseperators[1] = 0;
#endif

	vis = (long *)thread->base->portalvis;

	passage = portal->passages;
	nextpassage = passage;
	// check all portals for flowing into other leafs	
	for (i = 0; i < leaf->numportals; i++, passage = nextpassage)
	{
		p = leaf->portals[i];
		if (p->removed)
			continue;
		nextpassage = passage->next;
		pnum = p - portals;

		if ( ! (prevstack->mightsee[pnum >> 3] & (1<<(pnum&7)) ) )
			continue;	// can't possibly see it

		prevmight = (long *)prevstack->mightsee;
		cansee = (long *)passage->cansee;
		might = (long *)stack.mightsee;
		memcpy(might, prevmight, portalbytes);
		if (p->status == stat_done)
			portalvis = (long *) p->portalvis;
		else
			portalvis = (long *) p->portalflood;
		more = 0;
		for (j = 0; j < portallongs; j++)
		{
			if (*might)
			{
				*might &= *cansee++ & *portalvis++;
				more |= (*might & ~vis[j]);
			}
			else
			{
				cansee++;
				portalvis++;
			}
			might++;
		}

		if (!more && (thread->base->portalvis[pnum>>3] & (1<<(pnum&7))) )
		{	// can't see anything new
			continue;
		}

		// get plane of portal, point normal into the neighbor leaf
		stack.portalplane = p->plane;
		VectorSubtract (vec3_origin, p->plane.normal, backplane.normal);
		backplane.dist = -p->plane.dist;
		
//		c_portalcheck++;
		
		stack.portal = p;
		stack.next = NULL;
		stack.freewindings[0] = 1;
		stack.freewindings[1] = 1;
		stack.freewindings[2] = 1;

#if 1
		{
			float d;

			d = DotProduct (p->origin, thread->pstack_head.portalplane.normal);
			d -= thread->pstack_head.portalplane.dist;
			if (d < -p->radius)
			{
				continue;
			}
			else if (d > p->radius)
			{
				stack.pass = p->winding;
			}
			else	
			{
				stack.pass = VisChopWinding (p->winding, &stack, &thread->pstack_head.portalplane);
				if (!stack.pass)
					continue;
			}
		}
#else
		stack.pass = VisChopWinding (p->winding, &stack, &thread->pstack_head.portalplane);
		if (!stack.pass)
			continue;
#endif

	
#if 1
		{
			float d;

			d = DotProduct (thread->base->origin, p->plane.normal);
			d -= p->plane.dist;
			//MrE: vis-bug fix
			//if (d > p->radius)
			if (d > thread->base->radius)
			{
				continue;
			}
			//MrE: vis-bug fix
			//if (d < -p->radius)
			else if (d < -thread->base->radius)
			{
				stack.source = prevstack->source;
			}
			else	
			{
				stack.source = VisChopWinding (prevstack->source, &stack, &backplane);
				//FIXME: shouldn't we create a new source origin and radius for fast checks?
				if (!stack.source)
					continue;
			}
		}
#else
		stack.source = VisChopWinding (prevstack->source, &stack, &backplane);
		if (!stack.source)
			continue;
#endif

		if (!prevstack->pass)
		{	// the second leaf can only be blocked if coplanar

			// mark the portal as visible
			thread->base->portalvis[pnum>>3] |= (1<<(pnum&7));

			RecursivePassagePortalFlow (p, thread, &stack);
			continue;
		}

#ifdef SEPERATORCACHE
		if (stack.numseperators[0])
		{
			for (n = 0; n < stack.numseperators[0]; n++)
			{
				stack.pass = VisChopWinding (stack.pass, &stack, &stack.seperators[0][n]);
				if (!stack.pass)
					break;		// target is not visible
			}
			if (n < stack.numseperators[0])
				continue;
		}
		else
		{
			stack.pass = ClipToSeperators (prevstack->source, prevstack->pass, stack.pass, qfalse, &stack);
		}
#else
		stack.pass = ClipToSeperators (stack.source, prevstack->pass, stack.pass, qfalse, &stack);
#endif
		if (!stack.pass)
			continue;

#ifdef SEPERATORCACHE
		if (stack.numseperators[1])
		{
			for (n = 0; n < stack.numseperators[1]; n++)
			{
				stack.pass = VisChopWinding (stack.pass, &stack, &stack.seperators[1][n]);
				if (!stack.pass)
					break;		// target is not visible
			}
		}
		else
		{
			stack.pass = ClipToSeperators (prevstack->pass, prevstack->source, stack.pass, qtrue, &stack);
		}
#else
		stack.pass = ClipToSeperators (prevstack->pass, stack.source, stack.pass, qtrue, &stack);
#endif
		if (!stack.pass)
			continue;

		// mark the portal as visible
		thread->base->portalvis[pnum>>3] |= (1<<(pnum&7));

		// flow through it for real
		RecursivePassagePortalFlow(p, thread, &stack);
		//
		stack.next = NULL;
	}
}