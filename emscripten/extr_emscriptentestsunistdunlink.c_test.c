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
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 scalar_t__ EACCES ; 
 scalar_t__ EBUSY ; 
 scalar_t__ EISDIR ; 
 scalar_t__ ENOENT ; 
 scalar_t__ ENOTDIR ; 
 scalar_t__ ENOTEMPTY ; 
 scalar_t__ EPERM ; 
 int /*<<< orphan*/  F_OK ; 
 int access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  getcwd (char*,int) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int rmdir (char*) ; 
 int unlink (char*) ; 

void test() {
  int err;
  char buffer[512];

  //
  // test unlink
  //
  err = unlink("noexist");
  assert(err == -1);
  assert(errno == ENOENT);

  err = unlink("dir-readonly");
  assert(err == -1);

  // emscripten uses 'musl' what is an implementation of the standard library for Linux-based systems
#if defined(__linux__) || defined(__EMSCRIPTEN__)
  // Here errno is supposed to be EISDIR, but it is EPERM for NODERAWFS on macOS.
  // See issue #6121.
  assert(errno == EISDIR || errno == EPERM);
#else
  assert(errno == EPERM);
#endif

#ifndef SKIP_ACCESS_TESTS
  err = unlink("dir-readonly/anotherfile");
  assert(err == -1);
  assert(errno == EACCES);
#endif

#ifndef NO_SYMLINK
  // try unlinking the symlink first to make sure
  // we don't follow the link
  err = unlink("file1-link");
  assert(!err);
#endif
  err = access("file1", F_OK);
  assert(!err);
#ifndef NO_SYMLINK
  err = access("file1-link", F_OK);
  assert(err == -1);
#endif

  err = unlink("file");
  assert(!err);
  err = access("file", F_OK);
  assert(err == -1);

  //
  // test rmdir
  //
  err = rmdir("noexist");
  assert(err == -1);
  assert(errno == ENOENT);

  err = rmdir("file1");
  assert(err == -1);
  assert(errno == ENOTDIR);

#ifndef SKIP_ACCESS_TESTS
  err = rmdir("dir-readonly/anotherdir");
  assert(err == -1);
  assert(errno == EACCES);
#endif

  err = rmdir("dir-full");
  assert(err == -1);
  assert(errno == ENOTEMPTY);

  // test removing the cwd / root. The result isn't specified by
  // POSIX, but Linux seems to set EBUSY in both cases.
#ifndef __APPLE__
  getcwd(buffer, sizeof(buffer));
  err = rmdir(buffer);
  assert(err == -1);
#ifdef NODERAWFS
  assert(errno == ENOTEMPTY);
#else
  assert(errno == EBUSY);
#endif
#endif
  err = rmdir("/");
  assert(err == -1);
#ifdef __APPLE__
  assert(errno == EISDIR);
#else
  // errno is EISDIR for NODERAWFS on macOS. See issue #6121.
  assert(errno == EBUSY || errno == EISDIR);
#endif

#ifndef NO_SYMLINK
  err = rmdir("dir-empty-link");
  assert(err == -1);
  assert(errno == ENOTDIR);
#endif

  err = rmdir("dir-empty");
  assert(!err);
  err = access("dir-empty", F_OK);
  assert(err == -1);

  puts("success");
}