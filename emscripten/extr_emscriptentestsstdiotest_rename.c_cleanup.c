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
 int /*<<< orphan*/  rmdir (char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

void cleanup() {
  // we're hulk-smashing and removing original + renamed files to
  // make sure we get it all regardless of anything failing
  unlink("file");
  unlink("dir/file");
  unlink("dir/file1");
  unlink("dir/file2");
  rmdir("dir/subdir");
  rmdir("dir/subdir1");
  rmdir("dir/subdir2");
  rmdir("dir/subdir3/subdir3_1/subdir1 renamed");
  rmdir("dir/subdir3/subdir3_1");
  rmdir("dir/subdir3");
  rmdir("dir");
  rmdir("dir-readonly");
  unlink("dir-nonempty/file");
  rmdir("dir-nonempty");
}