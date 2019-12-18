#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_4__* next; scalar_t__ frmask; scalar_t__ brmask; scalar_t__ grmask; } ;
struct TYPE_7__ {TYPE_3__ p; } ;
struct TYPE_8__ {TYPE_1__ record; } ;
struct TYPE_10__ {TYPE_2__ r; struct TYPE_10__* next; } ;
typedef  TYPE_4__ unw_rec_list ;
struct TYPE_11__ {TYPE_3__* pending_saves; TYPE_4__* current_entry; TYPE_4__* tail; TYPE_4__* list; } ;

/* Variables and functions */
 int /*<<< orphan*/  as_warn (char*) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 TYPE_5__ unwind ; 

__attribute__((used)) static void
check_pending_save (void)
{
  if (unwind.pending_saves)
    {
      unw_rec_list *cur, *prev;

      as_warn ("Previous .save incomplete");
      for (cur = unwind.list, prev = NULL; cur; )
	if (&cur->r.record.p == unwind.pending_saves)
	  {
	    if (prev)
	      prev->next = cur->next;
	    else
	      unwind.list = cur->next;
	    if (cur == unwind.tail)
	      unwind.tail = prev;
	    if (cur == unwind.current_entry)
	      unwind.current_entry = cur->next;
	    /* Don't free the first discarded record, it's being used as
	       terminator for (currently) br_gr and gr_gr processing, and
	       also prevents leaving a dangling pointer to it in its
	       predecessor.  */
	    cur->r.record.p.grmask = 0;
	    cur->r.record.p.brmask = 0;
	    cur->r.record.p.frmask = 0;
	    prev = cur->r.record.p.next;
	    cur->r.record.p.next = NULL;
	    cur = prev;
	    break;
	  }
	else
	  {
	    prev = cur;
	    cur = cur->next;
	  }
      while (cur)
	{
	  prev = cur;
	  cur = cur->r.record.p.next;
	  free (prev);
	}
      unwind.pending_saves = NULL;
    }
}