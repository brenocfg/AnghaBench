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
struct aio_queue {int ref; int fd; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aio_fd_cnt ; 
 int /*<<< orphan*/  free (struct aio_queue*) ; 
 scalar_t__**** map ; 
 int /*<<< orphan*/  maplock ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_rwlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_rwlock_wrlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __aio_unref_queue(struct aio_queue *q)
{
	if (q->ref > 1) {
		q->ref--;
		pthread_mutex_unlock(&q->lock);
		return;
	}

	/* This is potentially the last reference, but a new reference
	 * may arrive since we cannot free the queue object without first
	 * taking the maplock, which requires releasing the queue lock. */
	pthread_mutex_unlock(&q->lock);
	pthread_rwlock_wrlock(&maplock);
	pthread_mutex_lock(&q->lock);
	if (q->ref == 1) {
		int fd=q->fd;
		int a=fd>>24;
		unsigned char b=fd>>16, c=fd>>8, d=fd;
		map[a][b][c][d] = 0;
		a_dec(&aio_fd_cnt);
		pthread_rwlock_unlock(&maplock);
		pthread_mutex_unlock(&q->lock);
		free(q);
	} else {
		q->ref--;
		pthread_rwlock_unlock(&maplock);
		pthread_mutex_unlock(&q->lock);
	}
}