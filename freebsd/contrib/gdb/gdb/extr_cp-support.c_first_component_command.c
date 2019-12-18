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
 char* alloca (int) ; 
 int cp_find_first_component (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,char*) ; 

__attribute__((used)) static void
first_component_command (char *arg, int from_tty)
{
  int len = cp_find_first_component (arg);
  char *prefix = alloca (len + 1);

  memcpy (prefix, arg, len);
  prefix[len] = '\0';

  printf_unfiltered ("%s\n", prefix);
}