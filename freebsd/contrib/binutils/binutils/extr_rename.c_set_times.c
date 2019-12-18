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
typedef  long utimbuf ;
struct timeval {long tv_sec; scalar_t__ tv_usec; } ;
struct stat {long st_atime; long st_mtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  non_fatal (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int utime (char const*,long*) ; 
 int utimes (char const*,struct timeval*) ; 

void
set_times (const char *destination, const struct stat *statbuf)
{
  int result;

  {
#ifdef HAVE_GOOD_UTIME_H
    struct utimbuf tb;

    tb.actime = statbuf->st_atime;
    tb.modtime = statbuf->st_mtime;
    result = utime (destination, &tb);
#else /* ! HAVE_GOOD_UTIME_H */
#ifndef HAVE_UTIMES
    long tb[2];

    tb[0] = statbuf->st_atime;
    tb[1] = statbuf->st_mtime;
    result = utime (destination, tb);
#else /* HAVE_UTIMES */
    struct timeval tv[2];

    tv[0].tv_sec = statbuf->st_atime;
    tv[0].tv_usec = 0;
    tv[1].tv_sec = statbuf->st_mtime;
    tv[1].tv_usec = 0;
    result = utimes (destination, tv);
#endif /* HAVE_UTIMES */
#endif /* ! HAVE_GOOD_UTIME_H */
  }

  if (result != 0)
    non_fatal (_("%s: cannot set time: %s"), destination, strerror (errno));
}