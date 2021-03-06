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
struct TYPE_8__ {TYPE_2__* key; struct TYPE_8__* prevThread; struct TYPE_8__* nextThread; TYPE_1__* thread; struct TYPE_8__* prevKey; struct TYPE_8__* nextKey; } ;
typedef  TYPE_3__ ThreadKeyAssoc ;
struct TYPE_7__ {TYPE_3__* threads; } ;
struct TYPE_6__ {TYPE_3__* nextAssoc; TYPE_3__* keys; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_3__*) ; 

void pte_tkAssocDestroy (ThreadKeyAssoc * assoc)
   /*
    * -------------------------------------------------------------------
    * This routine releases all resources for the given ThreadKeyAssoc
    * once it is no longer being referenced
    * ie) either the key or thread has stopped referencing it.
    *
    * Parameters:
    *              assoc
    *                      an instance of ThreadKeyAssoc.
    * Returns:
    *      N/A
    * -------------------------------------------------------------------
    */
{
   ThreadKeyAssoc *prev = NULL;
   ThreadKeyAssoc *next = NULL;
   /*
    * Both key->keyLock and thread->threadLock are locked on
    * entry to this routine.
    */
   if (!assoc)
      return;

   /* Remove assoc from thread's keys chain */
   prev = assoc->prevKey;
   next = assoc->nextKey;
   if (prev)
      prev->nextKey = next;
   if (next)
      next->prevKey = prev;

   /* We're at the head of the thread's keys chain */
   if (assoc->thread->keys == assoc)
      assoc->thread->keys = next;

   if (assoc->thread->nextAssoc == assoc)
   {
      /*
       * Thread is exiting and we're deleting the assoc to be processed next.
       * Hand thread the assoc after this one.
       */
      assoc->thread->nextAssoc = next;
   }

   /* Remove assoc from key's threads chain */
   prev = assoc->prevThread;
   next = assoc->nextThread;
   if (prev)
      prev->nextThread = next;
   if (next)
      next->prevThread = prev;

   /* We're at the head of the key's threads chain */
   if (assoc->key->threads == assoc)
      assoc->key->threads = next;

   free (assoc);
}