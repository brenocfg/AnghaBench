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
struct lio_state {int cnt; struct aiocb** cbs; } ;
struct aiocb {int dummy; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int /*<<< orphan*/  EIO ; 
 int aio_error (struct aiocb*) ; 
 scalar_t__ aio_suspend (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static int lio_wait(struct lio_state *st)
{
	int i, err, got_err = 0;
	int cnt = st->cnt;
	struct aiocb **cbs = st->cbs;

	for (;;) {
		for (i=0; i<cnt; i++) {
			if (!cbs[i]) continue;
			err = aio_error(cbs[i]);
			if (err==EINPROGRESS)
				break;
			if (err) got_err=1;
			cbs[i] = 0;
		}
		if (i==cnt) {
			if (got_err) {
				errno = EIO;
				return -1;
			}
			return 0;
		}
		if (aio_suspend((void *)cbs, cnt, 0))
			return -1;
	}
}