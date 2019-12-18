#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct deflect_struc {struct deflect_struc* prev; struct deflect_struc* next; int /*<<< orphan*/  rule; } ;
typedef  int /*<<< orphan*/  divert_rule ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  divert_lock ; 
 struct deflect_struc* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct deflect_struc* table_head ; 
 struct deflect_struc* table_tail ; 

int insertrule(int idx, divert_rule *newrule)
{ struct deflect_struc *ds,*ds1=NULL;
  unsigned long flags;

  if (!(ds = kmalloc(sizeof(struct deflect_struc),
                                              GFP_KERNEL))) 
    return(-ENOMEM); /* no memory */

  ds->rule = *newrule; /* set rule */

  spin_lock_irqsave(&divert_lock, flags);

  if (idx >= 0)
   { ds1 = table_head;
     while ((ds1) && (idx > 0))
      { idx--;
        ds1 = ds1->next;
      } 
     if (!ds1) idx = -1; 
   }

  if (idx < 0)
   { ds->prev = table_tail; /* previous entry */
     ds->next = NULL; /* end of chain */
     if (ds->prev) 
       ds->prev->next = ds; /* last forward */
      else
        table_head = ds; /* is first entry */
     table_tail = ds; /* end of queue */
   }
  else
    { ds->next = ds1; /* next entry */
      ds->prev = ds1->prev; /* prev entry */
      ds1->prev = ds; /* backward chain old element */
      if (!ds->prev)
        table_head = ds; /* first element */
   }

  spin_unlock_irqrestore(&divert_lock, flags);
  return(0);
}