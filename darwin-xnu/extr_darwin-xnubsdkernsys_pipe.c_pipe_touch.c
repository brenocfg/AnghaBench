#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timespec {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_5__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_4__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_6__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct pipe {TYPE_2__ st_ctimespec; TYPE_1__ st_mtimespec; TYPE_3__ st_atimespec; } ;

/* Variables and functions */
 int PIPE_ATIME ; 
 int PIPE_CTIME ; 
 int PIPE_MTIME ; 
 int /*<<< orphan*/  nanotime (struct timespec*) ; 

__attribute__((used)) static void
pipe_touch(struct pipe *tpipe, int touch)
{
	struct timespec now;

	nanotime(&now);

	if (touch & PIPE_ATIME) {
		tpipe->st_atimespec.tv_sec  = now.tv_sec;
		tpipe->st_atimespec.tv_nsec = now.tv_nsec;
	}

	if (touch & PIPE_MTIME) {
		tpipe->st_mtimespec.tv_sec  = now.tv_sec;
		tpipe->st_mtimespec.tv_nsec = now.tv_nsec;
	}

	if (touch & PIPE_CTIME) {
		tpipe->st_ctimespec.tv_sec  = now.tv_sec;
		tpipe->st_ctimespec.tv_nsec = now.tv_nsec;
	}
}