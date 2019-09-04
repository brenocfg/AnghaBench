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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 scalar_t__ EACCES ; 
 scalar_t__ EEXIST ; 
 int S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memset (struct stat*,int /*<<< orphan*/ ,int) ; 
 int mkdir (char*,int) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 

void test() {
  int err;
  struct stat s;

  //
  // mknod
  // mknod is _extremely_ unportable for anything other
  // than a FIFO. so, the tests are disabled when running
  // natively as they'd be utterly inconsistent.
  //
#ifdef __EMSCRIPTEN__

  // mknod a folder
  err = mknod("mknod-folder", S_IFDIR | 0777, 0);
  assert(err);
  assert(errno == EINVAL);

  // mknod fifo
  err = mknod("mknod-fifo", S_IFIFO | 0777, 0);
  assert(err);
  assert(errno == EPERM);

  // mknod a file
  err = mknod("mknod-file", S_IFREG | 0777, 0);
  assert(!err);
  memset(&s, 0, sizeof s);
  stat("mknod-file", &s);
  assert(S_ISREG(s.st_mode));

  // mknod a character device
  err = mknod("mknod-device", S_IFCHR | 0777, 123);
  assert(!err);
  memset(&s, 0, sizeof s);
  stat("mknod-device", &s);
  assert(S_ISCHR(s.st_mode));

#endif

  //
  // mkdir
  //
  // can't mkdir in a readonly dir
  err = mkdir("folder-readonly/subfolder", 0777);
  assert(err);
  assert(errno == EACCES);

  // regular creation
  err = mkdir("folder", 0777);
  assert(!err);
  memset(&s, 0, sizeof s);
  stat("folder", &s);
  assert(S_ISDIR(s.st_mode));

  // try to re-create the same folder
  err = mkdir("folder", 0777);
  assert(err);
  assert(errno == EEXIST);

  puts("success");
}