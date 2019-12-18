#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  m; int /*<<< orphan*/  i; int /*<<< orphan*/  r; } ;
struct TYPE_4__ {int /*<<< orphan*/ * r; int /*<<< orphan*/ * i; } ;
struct undo {int kind; struct undo* next; TYPE_2__ old_contents; TYPE_1__ where; } ;
struct TYPE_6__ {struct undo* undos; struct undo* frees; } ;

/* Variables and functions */
 int /*<<< orphan*/  PUT_MODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  UNDO_INT 130 
#define  UNDO_MODE 129 
#define  UNDO_RTX 128 
 int /*<<< orphan*/  gcc_unreachable () ; 
 TYPE_3__ undobuf ; 

__attribute__((used)) static void
undo_all (void)
{
  struct undo *undo, *next;

  for (undo = undobuf.undos; undo; undo = next)
    {
      next = undo->next;
      switch (undo->kind)
	{
	case UNDO_RTX:
	  *undo->where.r = undo->old_contents.r;
	  break;
	case UNDO_INT:
	  *undo->where.i = undo->old_contents.i;
	  break;
	case UNDO_MODE:
	  PUT_MODE (*undo->where.r, undo->old_contents.m);
	  break;
	default:
	  gcc_unreachable ();
	}

      undo->next = undobuf.frees;
      undobuf.frees = undo;
    }

  undobuf.undos = 0;
}