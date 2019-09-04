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
struct aio_queue {int fd; int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; } ;

/* Variables and functions */
 int /*<<< orphan*/  a_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aio_fd_cnt ; 
 void* calloc (int,int) ; 
 struct aio_queue***** map ; 
 int /*<<< orphan*/  maplock ; 
 int /*<<< orphan*/  pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_rwlock_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_rwlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_rwlock_wrlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct aio_queue *__aio_get_queue(int fd, int need)
{
	if (fd < 0) return 0;
	int a=fd>>24;
	unsigned char b=fd>>16, c=fd>>8, d=fd;
	struct aio_queue *q = 0;
	pthread_rwlock_rdlock(&maplock);
	if ((!map || !map[a] || !map[a][b] || !map[a][b][c] || !(q=map[a][b][c][d])) && need) {
		pthread_rwlock_unlock(&maplock);
		pthread_rwlock_wrlock(&maplock);
		if (!map) map = calloc(sizeof *map, (-1U/2+1)>>24);
		if (!map) goto out;
		if (!map[a]) map[a] = calloc(sizeof **map, 256);
		if (!map[a]) goto out;
		if (!map[a][b]) map[a][b] = calloc(sizeof ***map, 256);
		if (!map[a][b]) goto out;
		if (!map[a][b][c]) map[a][b][c] = calloc(sizeof ****map, 256);
		if (!map[a][b][c]) goto out;
		if (!(q = map[a][b][c][d])) {
			map[a][b][c][d] = q = calloc(sizeof *****map, 1);
			if (q) {
				q->fd = fd;
				pthread_mutex_init(&q->lock, 0);
				pthread_cond_init(&q->cond, 0);
				a_inc(&aio_fd_cnt);
			}
		}
	}
	if (q) pthread_mutex_lock(&q->lock);
out:
	pthread_rwlock_unlock(&maplock);
	return q;
}