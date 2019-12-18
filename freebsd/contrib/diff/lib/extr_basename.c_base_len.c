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
 scalar_t__ ISSLASH (char const) ; 
 size_t strlen (char const*) ; 

size_t
base_len (char const *name)
{
  size_t len;

  for (len = strlen (name);  1 < len && ISSLASH (name[len - 1]);  len--)
    continue;

  return len;
}