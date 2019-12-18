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
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 char* find_separate_debug_file (int /*<<< orphan*/ *,char const*) ; 

char *
bfd_follow_gnu_debuglink (bfd *abfd, const char *dir)
{
  return find_separate_debug_file (abfd, dir);
}