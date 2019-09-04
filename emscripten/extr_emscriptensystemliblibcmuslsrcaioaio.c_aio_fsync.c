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
struct aiocb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int O_DSYNC ; 
 int O_SYNC ; 
 int /*<<< orphan*/  errno ; 
 int submit (struct aiocb*,int) ; 

int aio_fsync(int op, struct aiocb *cb)
{
	if (op != O_SYNC && op != O_DSYNC) {
		errno = EINVAL;
		return -1;
	}
	return submit(cb, op);
}