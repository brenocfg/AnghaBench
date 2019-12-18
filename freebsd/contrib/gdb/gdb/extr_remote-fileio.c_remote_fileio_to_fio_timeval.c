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
struct timeval {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct fio_timeval {int /*<<< orphan*/  ftv_usec; int /*<<< orphan*/  ftv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  remote_fileio_to_fio_long (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remote_fileio_to_fio_time (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
remote_fileio_to_fio_timeval (struct timeval *tv, struct fio_timeval *ftv)
{
  remote_fileio_to_fio_time (tv->tv_sec, ftv->ftv_sec);
  remote_fileio_to_fio_long (tv->tv_usec, ftv->ftv_usec);
}