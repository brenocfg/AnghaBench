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
struct stat {int st_ctime; int st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_WRONLY ; 
 int S_IFDIR ; 
 int S_IFLNK ; 
 int S_IFREG ; 
 int /*<<< orphan*/  assert (int) ; 
 int chmod (char*,int) ; 
 int fchmod (int /*<<< orphan*/ ,int) ; 
 int lchmod (char*,int) ; 
 int /*<<< orphan*/  lstat (char*,struct stat*) ; 
 int /*<<< orphan*/  memset (struct stat*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 

void test() {
  int err;
  int lastctime;
  struct stat s;
  
  //
  // chmod a file
  //
  // get the current ctime for the file
  memset(&s, 0, sizeof s);
  stat("file", &s);
  lastctime = s.st_ctime;
  sleep(1);

  // do the actual chmod
  err = chmod("file", 0200);
  assert(!err);

  memset(&s, 0, sizeof s);
  stat("file", &s);
  assert(s.st_mode == (0200 | S_IFREG));
  assert(s.st_ctime != lastctime);

  //
  // fchmod a file
  //
  lastctime = s.st_ctime;
  sleep(1);

  err = fchmod(open("file", O_WRONLY), 0100);
  assert(!err);

  memset(&s, 0, sizeof s);
  stat("file", &s);
  assert(s.st_mode == (0100 | S_IFREG));
  assert(s.st_ctime != lastctime);

  //
  // chmod a folder
  //
  // get the current ctime for the folder
  memset(&s, 0, sizeof s);
  stat("folder", &s);
  lastctime = s.st_ctime;
  sleep(1);

  // do the actual chmod
  err = chmod("folder", 0300);
  assert(!err);
  memset(&s, 0, sizeof s);
  stat("folder", &s);
  assert(s.st_mode == (0300 | S_IFDIR));
  assert(s.st_ctime != lastctime);

  //
  // chmod a symlink's target
  //
  err = chmod("file-link", 0400);
  assert(!err);

  // make sure the file it references changed
  stat("file-link", &s);
  assert(s.st_mode == (0400 | S_IFREG));

  // but the link didn't
  lstat("file-link", &s);
  assert(s.st_mode == (0777 | S_IFLNK));

  //
  // chmod the actual symlink
  //
  err = lchmod("file-link", 0500);
  assert(err); // linux does not support lchmod, and neither does our libc, musl

  // make sure the file it references didn't change
  stat("file-link", &s);
  assert(s.st_mode == (0400 | S_IFREG));

  puts("success");
}