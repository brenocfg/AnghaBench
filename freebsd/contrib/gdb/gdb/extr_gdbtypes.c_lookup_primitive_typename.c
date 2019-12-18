#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct type {int dummy; } ;
struct TYPE_2__ {struct type*** la_builtin_type_vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_NAME (struct type*) ; 
 TYPE_1__* current_language ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

struct type *
lookup_primitive_typename (char *name)
{
  struct type **const *p;

  for (p = current_language->la_builtin_type_vector; *p != NULL; p++)
    {
      if (strcmp (TYPE_NAME (**p), name) == 0)
	{
	  return (**p);
	}
    }
  return (NULL);
}