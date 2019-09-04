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
 scalar_t__ EACCES ; 
 scalar_t__ EINVAL ; 
 scalar_t__ EISDIR ; 
 scalar_t__ ENOENT ; 
 scalar_t__ ENOTDIR ; 
 scalar_t__ ENOTEMPTY ; 
 int /*<<< orphan*/  F_OK ; 
 int access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  puts (char*) ; 
 int rename (char*,char*) ; 

void test() {
  int err;

  // can't rename something that doesn't exist
  err = rename("noexist", "dir");
  assert(err == -1);
  assert(errno == ENOENT);

  // can't overwrite a folder with a file
  err = rename("file", "dir");
  assert(err == -1);
  assert(errno == EISDIR);

  // can't overwrite a file with a folder
  err = rename("dir", "file");
  assert(err == -1);
  assert(errno == ENOTDIR);

  // can't overwrite a non-empty folder
  err = rename("dir", "dir-nonempty");
  assert(err == -1);
  assert(errno == ENOTEMPTY);

  // can't create anything in a read-only directory
  err = rename("dir", "dir-readonly/dir");
  assert(err == -1);
  assert(errno == EACCES);

  // source should not be ancestor of target
  err = rename("dir", "dir/somename");
  assert(err == -1);
  assert(errno == EINVAL);

  // target should not be an ancestor of source
  err = rename("dir/subdir", "dir");
  assert(err == -1);
  assert(errno == ENOTEMPTY);

  // do some valid renaming
  err = rename("dir/file", "dir/file1");
  assert(!err);
  err = rename("dir/file1", "dir/file2");
  assert(!err);
  err = access("dir/file2", F_OK);
  assert(!err);
  err = rename("dir/subdir", "dir/subdir1");
  assert(!err);
  err = rename("dir/subdir1", "dir/subdir2");
  assert(!err);
  err = access("dir/subdir2", F_OK);
  assert(!err);

  err = rename("dir/subdir2", "dir/subdir3/subdir3_1/subdir1 renamed");
  assert(!err);
  err = access("dir/subdir3/subdir3_1/subdir1 renamed", F_OK);
  assert(!err);

  puts("success");
}