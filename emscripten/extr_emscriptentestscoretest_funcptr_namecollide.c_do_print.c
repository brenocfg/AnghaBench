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
 int /*<<< orphan*/  do_call (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  puts (char const*) ; 

void do_print(const char *str) {
  if (!str) do_call(NULL, "delusion");
  if ((int)str == -1) do_print(str + 10);
  puts("====");
  puts(str);
  puts("====");
}