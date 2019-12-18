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
struct deflect_struc {struct deflect_struc* next; TYPE_1__* prev; } ;
struct TYPE_2__ {struct deflect_struc* next; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  divert_lock ; 
 int /*<<< orphan*/  kfree (struct deflect_struc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct deflect_struc* table_head ; 
 TYPE_1__* table_tail ; 

int deleterule(int idx)
{ struct deflect_struc *ds,*ds1;
  unsigned long flags;
  
  if (idx < 0) 
   { spin_lock_irqsave(&divert_lock, flags);
     ds = table_head;
     table_head = NULL;
     table_tail = NULL;
     spin_unlock_irqrestore(&divert_lock, flags);
     while (ds)
      { ds1 = ds; 
        ds = ds->next;
        kfree(ds1);
      } 
     return(0); 
   }

  spin_lock_irqsave(&divert_lock, flags);
  ds = table_head;

  while ((ds) && (idx > 0))
   { idx--; 
     ds = ds->next;  
   }

  if (!ds) 
   {
     spin_unlock_irqrestore(&divert_lock, flags);
     return(-EINVAL);
   }  

  if (ds->next) 
    ds->next->prev = ds->prev; /* backward chain */
   else
     table_tail = ds->prev; /* end of chain */

  if (ds->prev)
    ds->prev->next = ds->next; /* forward chain */
   else
     table_head = ds->next; /* start of chain */      
  
  spin_unlock_irqrestore(&divert_lock, flags);
  kfree(ds);
  return(0);
}