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

/* Variables and functions */
 int EBADF ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  assert (int) ; 
 int close (int) ; 
 int errno ; 
 int fsync (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

int main() {
  int f = open(".", O_RDONLY);

  int ret = fsync(f);
  printf("fsync(opened): %d\n", ret);
  printf("errno: %d\n", errno);
  assert(ret == 0);
  assert(errno == 0);
  errno = 0;

  ret = close(f);
  printf("close(opened): %d\n", ret);
  printf("errno: %d\n", errno);
  assert(ret == 0);
  assert(errno == 0);
  errno = 0;

  ret = fsync(f);
  printf("fsync(closed): %d\n", ret);
  printf("errno: %d\n", errno);
  assert(ret == -1);
  assert(errno == EBADF);
  errno = 0;

  ret = close(f);
  printf("close(closed): %d\n", ret);
  printf("errno: %d\n", errno);
  assert(ret == -1);
  assert(errno == EBADF);
  errno = 0;

#ifdef REPORT_RESULT
  REPORT_RESULT(0);
#endif
  return 0;
}