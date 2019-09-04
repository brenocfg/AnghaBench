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
 int /*<<< orphan*/  EINVAL ; 
 int __add_to_environ (char const*,char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  __set_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 

int
setenv (const char *name, const char *value, int replace)
{
  if (name == NULL || *name == '\0' || strchr (name, '=') != NULL)
    {
      __set_errno (EINVAL);
      return -1;
    }

  return __add_to_environ (name, value, NULL, replace);
}