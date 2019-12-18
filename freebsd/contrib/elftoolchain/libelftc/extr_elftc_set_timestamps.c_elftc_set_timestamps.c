#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct utimbuf {int /*<<< orphan*/  modtime; int /*<<< orphan*/  actime; } ;
struct timeval {int tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_4__ {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_3__ {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct stat {int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_atime; TYPE_2__ MTIME; TYPE_1__ ATIME; } ;

/* Variables and functions */
 int utime (char const*,struct utimbuf*) ; 
 int utimes (char const*,struct timeval*) ; 

int
elftc_set_timestamps(const char *fn, struct stat *sb)
{
#if	LIBELFTC_HAVE_UTIMES
	/*
	 * The BSD utimes() system call offers timestamps
	 * 1-microsecond granularity.
	 */
	struct timeval tv[2];

	tv[0].tv_sec = sb->ATIME.tv_sec;
	tv[0].tv_usec = sb->ATIME.tv_nsec / 1000;
	tv[1].tv_sec = sb->MTIME.tv_sec;
	tv[1].tv_usec = sb->MTIME.tv_nsec / 1000;

	return (utimes(fn, tv));
#else
	/*
	 * On OSes without utimes(), fall back to the POSIX utime()
	 * call, which offers 1-second granularity.
	 */
	struct utimbuf utb;

	utb.actime = sb->st_atime;
	utb.modtime = sb->st_mtime;
	return (utime(fn, &utb));
#endif
}