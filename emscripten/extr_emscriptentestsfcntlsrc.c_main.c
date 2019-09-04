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
struct flock {int l_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_DUPFD ; 
 int F_GETFD ; 
 int F_GETFL ; 
 int /*<<< orphan*/  F_GETLK ; 
 int F_GETOWN ; 
 int F_SETFD ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  F_SETLK ; 
 int /*<<< orphan*/  F_SETOWN ; 
 int F_UNLCK ; 
 int O_APPEND ; 
 int O_RDWR ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 int fcntl (int,int,...) ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int main() {
  int f = open("test", O_RDWR, 0777);
  assert(f > 0);

  printf("F_DUPFD: %d\n", fcntl(f, F_DUPFD, 100) >= 100);
  printf("errno: %d\n", errno);
  printf("\n");
  errno = 0;

  printf("F_DUPFD/error1: %d\n", fcntl(50, F_DUPFD, 200));
  printf("errno: %d\n", errno);
  printf("\n");
  errno = 0;

  printf("F_DUPFD/error2: %d\n", fcntl(f, F_DUPFD, -1));
  printf("errno: %d\n", errno);
  printf("\n");
  errno = 0;

  printf("F_GETFD: %d\n", fcntl(f, F_GETFD));
  printf("errno: %d\n", errno);
  printf("\n");
  errno = 0;

  printf("F_SETFD: %d\n", fcntl(f, F_SETFD));
  printf("errno: %d\n", errno);
  printf("\n");
  errno = 0;

  printf("F_GETFL: %d\n", !!(fcntl(f, F_GETFL) & O_RDWR));
  printf("errno: %d\n", errno);
  printf("\n");
  errno = 0;

  printf("F_SETFL: %d\n", fcntl(f, F_SETFL, O_APPEND));
  printf("errno: %d\n", errno);
  printf("\n");
  errno = 0;

  printf("F_GETFL/2: %d\n", !!(fcntl(f, F_GETFL) & (O_RDWR | O_APPEND)));
  printf("errno: %d\n", errno);
  printf("\n");
  errno = 0;

  struct flock lk;
  lk.l_type = 42;
  printf("F_GETLK: %d\n", fcntl(f, F_GETLK, &lk));
  printf("errno: %d\n", errno);
  printf("lk.l_type == F_UNLCK: %d\n", lk.l_type == F_UNLCK);
  printf("\n");
  errno = 0;

  printf("F_SETLK: %d\n", fcntl(f, F_SETLK, &lk));
  printf("errno: %d\n", errno);
  printf("\n");
  errno = 0;

  printf("F_SETLKW: %d\n", fcntl(f, F_SETLK, &lk));
  printf("errno: %d\n", errno);
  printf("\n");
  errno = 0;

  printf("F_SETOWN: %d\n", fcntl(f, F_SETOWN, 123));
  printf("errno: %d\n", errno);
  printf("\n");
  errno = 0;

  printf("F_GETOWN: %d\n", fcntl(f, F_GETOWN));
  printf("errno: %d\n", errno);
  printf("\n");
  errno = 0;

  printf("INVALID: %d\n", fcntl(f, 123));
  printf("errno: %d\n", errno);

  return 0;
}