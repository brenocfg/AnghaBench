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
struct test {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 
 struct test const* tests ; 

__attribute__((used)) static const struct test *find_test(const char *name)
{
  if (name == NULL)
    {
      return tests + 0;
    }
  else
    {
      for (const struct test *p = tests; p->name != NULL; p++)
	{
          if (strcmp(p->name, name) == 0)
	    {
              return p;
	    }
	}
    }

  return NULL;
}