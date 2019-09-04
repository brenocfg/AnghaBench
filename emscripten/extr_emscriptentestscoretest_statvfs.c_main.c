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
struct statvfs {int f_bsize; int f_frsize; int f_blocks; int f_bfree; int f_bavail; int f_files; int f_ffree; int f_favail; int f_fsid; int f_flag; int f_namemax; } ;

/* Variables and functions */
 int errno ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int statvfs (char*,struct statvfs*) ; 

int main() {
  struct statvfs s;

  printf("result: %d\n", statvfs("/test", &s));
  printf("errno: %d\n", errno);

  printf("f_bsize: %lu\n", s.f_bsize);
  printf("f_frsize: %lu\n", s.f_frsize);
  printf("f_blocks: %lu\n", s.f_blocks);
  printf("f_bfree: %lu\n", s.f_bfree);
  printf("f_bavail: %lu\n", s.f_bavail);
  printf("f_files: %d\n", s.f_files > 5);
  printf("f_ffree: %lu\n", s.f_ffree);
  printf("f_favail: %lu\n", s.f_favail);
  printf("f_fsid: %lu\n", s.f_fsid);
  printf("f_flag: %lu\n", s.f_flag);
  printf("f_namemax: %lu\n", s.f_namemax);

  return 0;
}