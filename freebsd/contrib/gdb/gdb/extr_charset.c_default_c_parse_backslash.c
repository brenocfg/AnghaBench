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
 char const* backslashable ; 
 int host_char_to_target (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * represented ; 
 char* strchr (char const*,int) ; 

__attribute__((used)) static int
default_c_parse_backslash (void *baton, int host_char, int *target_char)
{
  const char *ix;

  ix = strchr (backslashable, host_char);

  if (! ix)
    return 0;
  else
    return host_char_to_target (represented[ix - backslashable],
                                target_char);
}