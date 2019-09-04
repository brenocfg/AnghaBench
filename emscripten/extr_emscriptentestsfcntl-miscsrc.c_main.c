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
struct stat {int st_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  POSIX_FADV_DONTNEED ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 int /*<<< orphan*/  memset (struct stat*,int /*<<< orphan*/ ,int) ; 
 int open (char*,int /*<<< orphan*/ ,int) ; 
 int posix_fadvise (int,int,int,int /*<<< orphan*/ ) ; 
 int posix_fallocate (int,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 

int main() {
  struct stat s;
  int f = open("/test", O_RDWR, 0777);
  assert(f);

  printf("posix_fadvise: %d\n", posix_fadvise(f, 3, 2, POSIX_FADV_DONTNEED));
  printf("errno: %d\n", errno);
  printf("\n");
  errno = 0;

  printf("posix_fallocate: %d\n", posix_fallocate(f, 3, 2));
  printf("errno: %d\n", errno);
  stat("/test", &s);
  printf("st_size: %d\n", s.st_size);
  memset(&s, 0, sizeof s);
  printf("\n");
  errno = 0;

  printf("posix_fallocate2: %d\n", posix_fallocate(f, 3, 7));
  printf("errno: %d\n", errno);
  stat("/test", &s);
  printf("st_size: %d\n", s.st_size);
  memset(&s, 0, sizeof s);

  return 0;
}