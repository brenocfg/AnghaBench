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
typedef  int /*<<< orphan*/ * pthread_rwlockattr_t ;
typedef  TYPE_1__* pthread_rwlock_t ;
struct TYPE_4__ {int /*<<< orphan*/  mtxExclusiveAccess; int /*<<< orphan*/  mtxSharedAccessCompleted; int /*<<< orphan*/  nMagic; int /*<<< orphan*/  cndSharedAccessCompleted; scalar_t__ nCompletedSharedAccessCount; scalar_t__ nExclusiveAccessCount; scalar_t__ nSharedAccessCount; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PTW32_RWLOCK_MAGIC ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ *) ; 
 int pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
pthread_rwlock_init (pthread_rwlock_t * rwlock,
		     const pthread_rwlockattr_t * attr)
{
  int result;
  pthread_rwlock_t rwl = 0;

  if (rwlock == NULL)
    {
      return EINVAL;
    }

  if (attr != NULL && *attr != NULL)
    {
      result = EINVAL;		/* Not supported */
      goto DONE;
    }

  rwl = (pthread_rwlock_t) calloc (1, sizeof (*rwl));

  if (rwl == NULL)
    {
      result = ENOMEM;
      goto DONE;
    }

  rwl->nSharedAccessCount = 0;
  rwl->nExclusiveAccessCount = 0;
  rwl->nCompletedSharedAccessCount = 0;

  result = pthread_mutex_init (&rwl->mtxExclusiveAccess, NULL);
  if (result != 0)
    {
      goto FAIL0;
    }

  result = pthread_mutex_init (&rwl->mtxSharedAccessCompleted, NULL);
  if (result != 0)
    {
      goto FAIL1;
    }

  result = pthread_cond_init (&rwl->cndSharedAccessCompleted, NULL);
  if (result != 0)
    {
      goto FAIL2;
    }

  rwl->nMagic = PTW32_RWLOCK_MAGIC;

  result = 0;
  goto DONE;

FAIL2:
  (void) pthread_mutex_destroy (&(rwl->mtxSharedAccessCompleted));

FAIL1:
  (void) pthread_mutex_destroy (&(rwl->mtxExclusiveAccess));

FAIL0:
  (void) free (rwl);
  rwl = NULL;

DONE:
  *rwlock = rwl;

  return result;
}