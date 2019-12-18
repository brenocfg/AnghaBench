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
struct spec_function {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 struct spec_function* static_spec_functions ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static const struct spec_function *
lookup_spec_function (const char *name)
{
  const struct spec_function *sf;

  for (sf = static_spec_functions; sf->name != NULL; sf++)
    if (strcmp (sf->name, name) == 0)
      return sf;

  return NULL;
}