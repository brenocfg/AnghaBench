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
 scalar_t__ current_host_charset ; 
 scalar_t__ current_target_charset ; 
 int /*<<< orphan*/  host_charset () ; 
 int /*<<< orphan*/  printf_filtered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_charset () ; 

__attribute__((used)) static void
show_charset (char *arg, int from_tty)
{
  if (current_host_charset == current_target_charset)
    {
      printf_filtered ("The current host and target character set is `%s'.\n",
                       host_charset ());
    }
  else
    {
      printf_filtered ("The current host character set is `%s'.\n",
                       host_charset ());
      printf_filtered ("The current target character set is `%s'.\n",
                       target_charset ());
    }
}