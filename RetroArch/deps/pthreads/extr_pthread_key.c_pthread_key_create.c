#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pthread_key_t ;
typedef  scalar_t__ pte_osResult ;
struct TYPE_4__ {void (* destructor ) (void*) ;int /*<<< orphan*/  keyLock; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 scalar_t__ PTE_OS_OK ; 
 int /*<<< orphan*/  PTHREAD_MUTEX_INITIALIZER ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ pte_osTlsAlloc (int /*<<< orphan*/ *) ; 

int
pthread_key_create (pthread_key_t * key, void (*destructor) (void *))
/*
 * ------------------------------------------------------
 * DOCPUBLIC
 *      This function creates a thread-specific data key visible
 *      to all threads. All existing and new threads have a value
 *      NULL for key until set using pthread_setspecific. When any
 *      thread with a non-NULL value for key terminates, 'destructor'
 *      is called with key's current value for that thread.
 *
 * PARAMETERS
 *      key
 *              pointer to an instance of pthread_key_t
 *
 *
 * DESCRIPTION
 *      This function creates a thread-specific data key visible
 *      to all threads. All existing and new threads have a value
 *      NULL for key until set using pthread_setspecific. When any
 *      thread with a non-NULL value for key terminates, 'destructor'
 *      is called with key's current value for that thread.
 *
 * RESULTS
 *              0               successfully created semaphore,
 *              EAGAIN          insufficient resources or PTHREAD_KEYS_MAX
 *                              exceeded,
 *              ENOMEM          insufficient memory to create the key,
 *
 * ------------------------------------------------------
 */
{
   int result = 0;
   pthread_key_t newkey;

   if ((newkey = (pthread_key_t) calloc (1, sizeof (*newkey))) == NULL)
      result = ENOMEM;
   else
   {
      pte_osResult osResult = pte_osTlsAlloc(&(newkey->key));

      if (osResult != PTE_OS_OK)
      {
         result = EAGAIN;

         free (newkey);
         newkey = NULL;
      }
      else if (destructor != NULL)
      {
         /*
          * Have to manage associations between thread and key;
          * Therefore, need a lock that allows multiple threads
          * to gain exclusive access to the key->threads list.
          *
          * The mutex will only be created when it is first locked.
          */
         newkey->keyLock = PTHREAD_MUTEX_INITIALIZER;
         newkey->destructor = destructor;
      }

   }

   *key = newkey;

   return (result);
}