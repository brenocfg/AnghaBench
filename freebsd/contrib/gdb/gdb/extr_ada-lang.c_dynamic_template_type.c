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
struct type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_TYPEDEF (struct type*) ; 
 scalar_t__ DEPRECATED_STREQ (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_STRUCT ; 
 struct type* ada_find_parallel_type (struct type*,char*) ; 
 int /*<<< orphan*/ * ada_type_name (struct type*) ; 
 int strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct type *
dynamic_template_type (struct type *type)
{
  CHECK_TYPEDEF (type);

  if (type == NULL || TYPE_CODE (type) != TYPE_CODE_STRUCT
      || ada_type_name (type) == NULL)
    return NULL;
  else
    {
      int len = strlen (ada_type_name (type));
      if (len > 6 && DEPRECATED_STREQ (ada_type_name (type) + len - 6, "___XVE"))
	return type;
      else
	return ada_find_parallel_type (type, "___XVE");
    }
}