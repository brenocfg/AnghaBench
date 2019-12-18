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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 scalar_t__ EBADF ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  T_ASSERT_GT (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  T_ASSERT_POSIX_SUCCESS (int,char*) ; 
 int /*<<< orphan*/  T_LOG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T_QUIET ; 
 int /*<<< orphan*/  T_SETUPBEGIN ; 
 int /*<<< orphan*/  T_SETUPEND ; 
 scalar_t__ errno ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

__attribute__((used)) static void *
reader_thread(void *arg)
{
	int fd = (int)arg;
	char c;

	T_SETUPBEGIN;
	T_QUIET;
	T_ASSERT_GT(fd, 0, "reader thread received valid fd");
	T_SETUPEND;

	for (;;) {
		ssize_t rdsize = read(fd, &c, sizeof(c));
		if (rdsize == -1) {
			if (errno == EINTR) {
				continue;
			} else if (errno == EBADF) {
				T_LOG("reader got an error (%s), shutting down", strerror(errno));
				return NULL;
			} else {
				T_ASSERT_POSIX_SUCCESS(rdsize, "read on PTY");
			}
		} else if (rdsize == 0) {
			return NULL;
		}
	}

	return NULL;
}