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
struct sound_queue {int busy; int non_blocking; int /*<<< orphan*/  open_queue; } ;
struct file {int f_mode; int f_flags; } ;
typedef  int fmode_t ;

/* Variables and functions */
 int EBUSY ; 
 int EINTR ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  SLEEP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int sq_allocate_buffers (struct sound_queue*,int,int) ; 
 int /*<<< orphan*/  sq_wake_up (struct sound_queue*,struct file*,int) ; 

__attribute__((used)) static int sq_open2(struct sound_queue *sq, struct file *file, fmode_t mode,
		    int numbufs, int bufsize)
{
	int rc = 0;

	if (file->f_mode & mode) {
		if (sq->busy) {
#if 0 /* blocking open() */
			rc = -EBUSY;
			if (file->f_flags & O_NONBLOCK)
				return rc;
			rc = -EINTR;
			while (sq->busy) {
				SLEEP(sq->open_queue);
				if (signal_pending(current))
					return rc;
			}
			rc = 0;
#else
			/* OSS manual says we will return EBUSY regardless
			   of O_NOBLOCK.
			*/
			return -EBUSY ;
#endif
		}
		sq->busy = 1; /* Let's play spot-the-race-condition */

		/* allocate the default number & size of buffers.
		   (i.e. specified in _setup() or as module params)
		   can't be changed at the moment - but _could_ be perhaps
		   in the setfragments ioctl.
		*/
		if (( rc = sq_allocate_buffers(sq, numbufs, bufsize))) {
#if 0 /* blocking open() */
			sq_wake_up(sq, file, mode);
#else
			sq->busy = 0 ;
#endif
			return rc;
		}

		sq->non_blocking = file->f_flags & O_NONBLOCK;
	}
	return rc;
}