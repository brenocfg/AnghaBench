#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pthread_condattr_t ;
typedef  TYPE_2__* pthread_cond_t ;
struct TYPE_9__ {struct TYPE_9__* next; struct TYPE_9__* prev; int /*<<< orphan*/  semBlockLock; int /*<<< orphan*/  semBlockQueue; int /*<<< orphan*/  mtxUnblockLock; scalar_t__ nWaitersGone; scalar_t__ nWaitersToUnblock; scalar_t__ nWaitersBlocked; } ;
struct TYPE_8__ {scalar_t__ pshared; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENOSYS ; 
 scalar_t__ PTHREAD_PROCESS_SHARED ; 
 scalar_t__ calloc (int,int) ; 
 int errno ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* pte_cond_list_head ; 
 int /*<<< orphan*/  pte_cond_list_lock ; 
 TYPE_2__* pte_cond_list_tail ; 
 int /*<<< orphan*/  pte_osMutexLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_osMutexUnlock (int /*<<< orphan*/ ) ; 
 int pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sem_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int pthread_cond_init (pthread_cond_t * cond, const pthread_condattr_t * attr)
   /*
    * ------------------------------------------------------
    * DOCPUBLIC
    *      This function initializes a condition variable.
    *
    * PARAMETERS
    *      cond
    *              pointer to an instance of pthread_cond_t
    *
    *      attr
    *              specifies optional creation attributes.
    *
    *
    * DESCRIPTION
    *      This function initializes a condition variable.
    *
    * RESULTS
    *              0               successfully created condition variable,
    *              EINVAL          'attr' is invalid,
    *              EAGAIN          insufficient resources (other than
    *                              memory,
    *              ENOMEM          insufficient memory,
    *              EBUSY           'cond' is already initialized,
    *
    * ------------------------------------------------------
    */
{
   int result;
   pthread_cond_t cv = NULL;

   if (cond == NULL)
      return EINVAL;

   if ((attr != NULL && *attr != NULL) &&
         ((*attr)->pshared == PTHREAD_PROCESS_SHARED))
   {
      /*
       * Creating condition variable that can be shared between
       * processes.
       */
      result = ENOSYS;
      goto DONE;
   }

   cv = (pthread_cond_t) calloc (1, sizeof (*cv));

   if (cv == NULL)
   {
      result = ENOMEM;
      goto DONE;
   }

   cv->nWaitersBlocked = 0;
   cv->nWaitersToUnblock = 0;
   cv->nWaitersGone = 0;

   if (sem_init (&(cv->semBlockLock), 0, 1) != 0)
   {
      result = errno;
      goto FAIL0;
   }

   if (sem_init (&(cv->semBlockQueue), 0, 0) != 0)
   {
      result = errno;
      goto FAIL1;
   }

   if ((result = pthread_mutex_init (&(cv->mtxUnblockLock), 0)) != 0)
   {
      goto FAIL2;
   }

   result = 0;

   goto DONE;

   /*
    * -------------
    * Failed...
    * -------------
    */
FAIL2:
   (void) sem_destroy (&(cv->semBlockQueue));

FAIL1:
   (void) sem_destroy (&(cv->semBlockLock));

FAIL0:
   (void) free (cv);
   cv = NULL;

DONE:
   if (0 == result)
   {

      pte_osMutexLock (pte_cond_list_lock);

      cv->next = NULL;
      cv->prev = pte_cond_list_tail;

      if (pte_cond_list_tail != NULL)
         pte_cond_list_tail->next = cv;

      pte_cond_list_tail = cv;

      if (pte_cond_list_head == NULL)
         pte_cond_list_head = cv;

      pte_osMutexUnlock(pte_cond_list_lock);
   }

   *cond = cv;

   return result;
}