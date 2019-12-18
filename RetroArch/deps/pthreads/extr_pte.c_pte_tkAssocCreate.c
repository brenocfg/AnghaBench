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
typedef  TYPE_1__* pthread_key_t ;
struct TYPE_7__ {void* keys; } ;
typedef  TYPE_2__ pte_thread_t ;
struct TYPE_8__ {struct TYPE_8__* prevKey; struct TYPE_8__* nextKey; struct TYPE_8__* prevThread; struct TYPE_8__* nextThread; TYPE_1__* key; TYPE_2__* thread; } ;
typedef  TYPE_3__ ThreadKeyAssoc ;
struct TYPE_6__ {void* threads; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ calloc (int,int) ; 

int pte_tkAssocCreate (pte_thread_t * sp, pthread_key_t key)
   /*
    * -------------------------------------------------------------------
    * This routine creates an association that
    * is unique for the given (thread,key) combination.The association
    * is referenced by both the thread and the key.
    * This association allows us to determine what keys the
    * current thread references and what threads a given key
    * references.
    * See the detailed description
    * at the beginning of this file for further details.
    *
    * Notes:
    *      1)      New associations are pushed to the beginning of the
    *              chain so that the internal pte_selfThreadKey association
    *              is always last, thus allowing selfThreadExit to
    *              be implicitly called last by pthread_exit.
    *      2)
    *
    * Parameters:
    *              thread
    *                      current running thread.
    *              key
    *                      key on which to create an association.
    * Returns:
    *       0              - if successful,
    *       ENOMEM         - not enough memory to create assoc or other object
    *       EINVAL         - an internal error occurred
    *       ENOSYS         - an internal error occurred
    * -------------------------------------------------------------------
    */
{
   ThreadKeyAssoc *assoc;

   /*
    * Have to create an association and add it
    * to both the key and the thread.
    *
    * Both key->keyLock and thread->threadLock are locked on
    * entry to this routine.
    */
   assoc = (ThreadKeyAssoc *) calloc (1, sizeof (*assoc));

   if (assoc == NULL)
      return ENOMEM;

   assoc->thread = sp;
   assoc->key    = key;

   /*
    * Register assoc with key
    */
   assoc->prevThread = NULL;
   assoc->nextThread = (ThreadKeyAssoc *) key->threads;
   if (assoc->nextThread)
      assoc->nextThread->prevThread = assoc;
   key->threads = (void *) assoc;

   /*
    * Register assoc with thread
    */
   assoc->prevKey = NULL;
   assoc->nextKey = (ThreadKeyAssoc *) sp->keys;
   if (assoc->nextKey)
      assoc->nextKey->prevKey = assoc;
   sp->keys = (void *) assoc;

   return (0);
}