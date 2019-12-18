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
struct TYPE_7__ {void* z; int height; scalar_t__ y; scalar_t__ x; TYPE_1__* subsector; } ;
typedef  TYPE_2__ mobj_t ;
typedef  int boolean ;
struct TYPE_8__ {scalar_t__ dy; scalar_t__ dx; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_6__ {int sector; } ;

/* Variables and functions */
 int P_CrossBSPNode (scalar_t__) ; 
 void* bottomslope ; 
 scalar_t__ numnodes ; 
 int numsectors ; 
 int* rejectmatrix ; 
 int sectors ; 
 int /*<<< orphan*/ * sightcounts ; 
 void* sightzstart ; 
 TYPE_3__ strace ; 
 scalar_t__ t2x ; 
 scalar_t__ t2y ; 
 void* topslope ; 
 int /*<<< orphan*/  validcount ; 

boolean
P_CheckSight
( mobj_t*	t1,
  mobj_t*	t2 )
{
    int		s1;
    int		s2;
    int		pnum;
    int		bytenum;
    int		bitnum;
    
    // First check for trivial rejection.

    // Determine subsector entries in REJECT table.
    s1 = (t1->subsector->sector - sectors);
    s2 = (t2->subsector->sector - sectors);
    pnum = s1*numsectors + s2;
    bytenum = pnum>>3;
    bitnum = 1 << (pnum&7);

    // Check in REJECT table.
    if (rejectmatrix[bytenum]&bitnum)
    {
	sightcounts[0]++;

	// can't possibly be connected
	return false;	
    }

    // An unobstructed LOS is possible.
    // Now look from eyes of t1 to any part of t2.
    sightcounts[1]++;

    validcount++;
	
    sightzstart = t1->z + t1->height - (t1->height>>2);
    topslope = (t2->z+t2->height) - sightzstart;
    bottomslope = (t2->z) - sightzstart;
	
    strace.x = t1->x;
    strace.y = t1->y;
    t2x = t2->x;
    t2y = t2->y;
    strace.dx = t2->x - t1->x;
    strace.dy = t2->y - t1->y;

    // the head node is the last node output
    return P_CrossBSPNode (numnodes-1);	
}