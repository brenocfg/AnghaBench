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
 scalar_t__ DEPRECATED_STREQN (char*,char*,int) ; 

int
is_ada_runtime_file (char *filename)
{
  return (DEPRECATED_STREQN (filename, "s-", 2) ||
	  DEPRECATED_STREQN (filename, "a-", 2) ||
	  DEPRECATED_STREQN (filename, "g-", 2) || DEPRECATED_STREQN (filename, "i-", 2));
}