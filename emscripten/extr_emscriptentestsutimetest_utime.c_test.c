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
struct utimbuf {int member_0; int member_1; scalar_t__ actime; scalar_t__ modtime; } ;
struct stat {scalar_t__ st_atime; scalar_t__ st_mtime; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memset (struct stat*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 
 int /*<<< orphan*/  utime (char*,struct utimbuf*) ; 

void test() {
  struct stat s;
  // currently, the most recent timestamp is shared for atime,
  // ctime and mtime. using unique values for each in the test
  // will fail
  struct utimbuf t = {1000000000, 1000000000};

  utime("writeable", &t);
  assert(!errno);
  memset(&s, 0, sizeof s);
  stat("writeable", &s);
  assert(s.st_atime == t.actime);
  assert(s.st_mtime == t.modtime);

  // write permissions aren't checked when setting node
  // attributes unless the user uid isn't the owner (so
  // therefor, this should work fine)
  utime("unwriteable", &t);
  assert(!errno);
  memset(&s, 0, sizeof s);
  stat("unwriteable", &s);
  assert(s.st_atime == t.actime);
  assert(s.st_mtime == t.modtime);

  puts("success");
}