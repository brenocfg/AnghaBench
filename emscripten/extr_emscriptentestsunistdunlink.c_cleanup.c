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
 int /*<<< orphan*/  chmod (char*,int) ; 
 int /*<<< orphan*/  rmdir (char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

void cleanup() {
  unlink("file");
  unlink("file1");
#ifndef NO_SYMLINK
  unlink("file1-link");
#endif
  rmdir("dir-empty");
#ifndef NO_SYMLINK
  unlink("dir-empty-link");
#endif
  chmod("dir-readonly", 0777);
  unlink("dir-readonly/anotherfile");
  rmdir("dir-readonly/anotherdir");
  rmdir("dir-readonly");
  unlink("dir-full/anotherfile");
  rmdir("dir-full");
}