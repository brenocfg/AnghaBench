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
 int /*<<< orphan*/  do_print (char*) ; 
 void stub1 (char const*) ; 

void do_call(void (*puts)(const char *), const char *str) {
  if (!str) do_print("confusion");
  if ((int)str == -1) do_call(NULL, str - 10);
  (*puts)(str);
}