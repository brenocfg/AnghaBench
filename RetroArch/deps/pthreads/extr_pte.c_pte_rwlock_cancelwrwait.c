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
typedef  TYPE_1__* pthread_rwlock_t ;
struct TYPE_2__ {int /*<<< orphan*/  mtxExclusiveAccess; int /*<<< orphan*/  mtxSharedAccessCompleted; int /*<<< orphan*/  nCompletedSharedAccessCount; int /*<<< orphan*/  nSharedAccessCount; } ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void pte_rwlock_cancelwrwait (void *arg)
{
  pthread_rwlock_t rwl = (pthread_rwlock_t) arg;

  rwl->nSharedAccessCount = -rwl->nCompletedSharedAccessCount;
  rwl->nCompletedSharedAccessCount = 0;

  (void) pthread_mutex_unlock (&(rwl->mtxSharedAccessCompleted));
  (void) pthread_mutex_unlock (&(rwl->mtxExclusiveAccess));
}