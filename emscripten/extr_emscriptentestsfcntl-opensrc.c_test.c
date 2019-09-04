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
struct stat {int st_mode; } ;

/* Variables and functions */
 int EEXIST ; 
 int EISDIR ; 
 int ENOENT ; 
 int O_APPEND ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  assert (int) ; 
 int creat (char*,int) ; 
 int errno ; 
 int /*<<< orphan*/  memset (struct stat*,int /*<<< orphan*/ ,int) ; 
 char* nonexistent_name ; 
 int open (char*,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int stat (char*,struct stat*) ; 

void test() {
  struct stat s;
  int modes[] = {O_RDONLY, O_WRONLY, O_RDWR};

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 16; j++) {
      int flags = modes[i];
      if (j & 0x1) flags |= O_CREAT;
      if (j & 0x2) flags |= O_EXCL;
      if (j & 0x4) flags |= O_TRUNC;
      if (j & 0x8) flags |= O_APPEND;

      printf("EXISTING FILE %d,%d\n", i, j);
      int success = open("test-file", flags, 0777) != -1;
      printf("success: %d\n", success);
      printf("errno: %d\n", errno);
      if ((flags & O_CREAT) && (flags & O_EXCL)) {
        assert(!success);
        assert(errno == EEXIST);
      } else {
        assert(success);
        assert(errno == 0);
      }
      errno = 0;

      int ret = stat("test-file", &s);
      assert(ret == 0);
      assert(errno == 0);
      printf("st_mode: 0%o\n", s.st_mode & 037777777000);
      assert((s.st_mode & 037777777000) == 0100000);
      memset(&s, 0, sizeof s);
      printf("\n");
      errno = 0;

      printf("EXISTING FOLDER %d,%d\n", i, j);
      success = open("test-folder", flags, 0777) != -1;
      printf("success: %d\n", success);
      printf("errno: %d\n", errno);
      if ((flags & O_CREAT) && (flags & O_EXCL)) {
        assert(!success);
        assert(errno == EEXIST);
      } else if ((flags & O_TRUNC) || i != 0 /*mode != O_RDONLY*/) {
        assert(!success);
        assert(errno == EISDIR);
      } else {
        assert(success);
        assert(errno == 0);
      }
      errno = 0;

      ret = stat("test-folder", &s);
      assert(ret == 0);
      assert(errno == 0);
      printf("st_mode: 0%o\n", s.st_mode & 037777777000);
      assert((s.st_mode & 037777777000) == 040000);
      memset(&s, 0, sizeof s);
      printf("\n");
      errno = 0;

      nonexistent_name[8] = 'a' + i;
      nonexistent_name[9] = 'a' + j;
      printf("NON-EXISTING %d,%d\n", i, j);
      success = open(nonexistent_name, flags, 0777) != -1;
      printf("success: %d\n", success);
      printf("errno: %d\n", errno);
      if ((flags & O_CREAT)) {
        assert(success);
        assert(errno == 0);
      } else {
        assert(!success);
        assert(errno == ENOENT);
      }

      ret = stat(nonexistent_name, &s);
      printf("st_mode: 0%o\n", s.st_mode & 037777777000);

      if ((flags & O_CREAT)) {
        assert(ret == 0);
        assert((s.st_mode & 037777777000) == 0100000);
      } else {
        assert(ret != 0);
        assert((s.st_mode & 037777777000) == 0);
      }

      memset(&s, 0, sizeof s);
      printf("\n");
      errno = 0;
    }
  }

  printf("CREAT\n");
  printf("success: %d\n", creat("creat-me", 0777) != -1);
  printf("errno: %d\n", errno);
  errno = 0;
}