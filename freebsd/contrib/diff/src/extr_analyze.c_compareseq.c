#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct partition {size_t xmid; size_t ymid; int lo_minimal; int hi_minimal; } ;
typedef  size_t lin ;
struct TYPE_2__ {int* changed; size_t* realindexes; } ;

/* Variables and functions */
 int /*<<< orphan*/  diag (size_t,size_t,size_t,size_t,int,struct partition*) ; 
 TYPE_1__* files ; 
 size_t* xvec ; 
 size_t* yvec ; 

__attribute__((used)) static void
compareseq (lin xoff, lin xlim, lin yoff, lin ylim, bool find_minimal)
{
  lin const *xv = xvec; /* Help the compiler.  */
  lin const *yv = yvec;

  /* Slide down the bottom initial diagonal. */
  while (xoff < xlim && yoff < ylim && xv[xoff] == yv[yoff])
    ++xoff, ++yoff;
  /* Slide up the top initial diagonal. */
  while (xlim > xoff && ylim > yoff && xv[xlim - 1] == yv[ylim - 1])
    --xlim, --ylim;

  /* Handle simple cases. */
  if (xoff == xlim)
    while (yoff < ylim)
      files[1].changed[files[1].realindexes[yoff++]] = 1;
  else if (yoff == ylim)
    while (xoff < xlim)
      files[0].changed[files[0].realindexes[xoff++]] = 1;
  else
    {
      struct partition part;

      /* Find a point of correspondence in the middle of the files.  */
      diag (xoff, xlim, yoff, ylim, find_minimal, &part);

      /* Use the partitions to split this problem into subproblems.  */
      compareseq (xoff, part.xmid, yoff, part.ymid, part.lo_minimal);
      compareseq (part.xmid, xlim, part.ymid, ylim, part.hi_minimal);
    }
}