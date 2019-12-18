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
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ lstat (char const*,struct stat*) ; 
 int unlink (char const*) ; 

int
unlink_if_ordinary (const char *name)
{
  struct stat st;

  if (lstat (name, &st) == 0
      && (S_ISREG (st.st_mode) || S_ISLNK (st.st_mode)))
    return unlink (name);

  return 1;
}