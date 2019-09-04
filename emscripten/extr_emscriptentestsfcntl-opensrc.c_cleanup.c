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
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 char* nonexistent_name ; 
 int /*<<< orphan*/  rmdir (char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

void cleanup() {
  unlink("test-file");
  rmdir("test-folder");
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 16; j++) {
      nonexistent_name[8] = 'a' + i;
      nonexistent_name[9] = 'a' + j;
      unlink(nonexistent_name);
    }
  }
  errno = 0;
  unlink("creat-me");
  assert(!errno);
}