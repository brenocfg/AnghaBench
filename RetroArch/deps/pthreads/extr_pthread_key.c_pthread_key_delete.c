#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pthread_key_t ;
struct TYPE_8__ {int /*<<< orphan*/  threadLock; } ;
typedef  TYPE_2__ pte_thread_t ;
struct TYPE_9__ {TYPE_2__* thread; } ;
typedef  TYPE_3__ ThreadKeyAssoc ;
struct TYPE_7__ {int /*<<< orphan*/  keyLock; int /*<<< orphan*/ * destructor; int /*<<< orphan*/  key; int /*<<< orphan*/ * threads; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  pte_osThreadSleep (int) ; 
 int /*<<< orphan*/  pte_osTlsFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_tkAssocDestroy (TYPE_3__*) ; 
 int pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int pthread_key_delete (pthread_key_t key)
   /*
    * ------------------------------------------------------
    * DOCPUBLIC
    *      This function deletes a thread-specific data key. This
    *      does not change the value of the thread specific data key
    *      for any thread and does not run the key's destructor
    *      in any thread so it should be used with caution.
    *
    * PARAMETERS
    *      key
    *              pointer to an instance of pthread_key_t
    *
    *
    * DESCRIPTION
    *      This function deletes a thread-specific data key. This
    *      does not change the value of the thread specific data key
    *      for any thread and does not run the key's destructor
    *      in any thread so it should be used with caution.
    *
    * RESULTS
    *              0               successfully deleted the key,
    *              EINVAL          key is invalid,
    *
    * ------------------------------------------------------
    */
{
   int result = 0;

   if (key != NULL)
   {
      if (key->threads != NULL &&
            key->destructor != NULL &&
            pthread_mutex_lock (&(key->keyLock)) == 0)
      {
         ThreadKeyAssoc *assoc;
         /*
          * Run through all Thread<-->Key associations
          * for this key.
          *
          * While we hold at least one of the locks guarding
          * the assoc, we know that the assoc pointed to by
          * key->threads is valid.
          */
         while ((assoc = (ThreadKeyAssoc *) key->threads) != NULL)
         {
            pte_thread_t * thread = assoc->thread;

            /* Finished */
            if (assoc == NULL)
               break;

            if (pthread_mutex_lock (&(thread->threadLock)) == 0)
            {
               /*
                * Since we are starting at the head of the key's threads
                * chain, this will also point key->threads at the next assoc.
                * While we hold key->keyLock, no other thread can insert
                * a new assoc via pthread_setspecific.
                */
               pte_tkAssocDestroy (assoc);
               (void) pthread_mutex_unlock (&(thread->threadLock));
            }
            else
            {
               /* Thread or lock is no longer valid? */
               pte_tkAssocDestroy (assoc);
            }
         }
         pthread_mutex_unlock (&(key->keyLock));
      }

      pte_osTlsFree (key->key);
      if (key->destructor != NULL)
      {
         /* A thread could be holding the keyLock */
         while (EBUSY == (result = pthread_mutex_destroy (&(key->keyLock))))
            pte_osThreadSleep(1); /* Ugly. */
      }

      free (key);
   }

   return (result);
}