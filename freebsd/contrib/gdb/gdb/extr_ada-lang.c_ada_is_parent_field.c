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
 scalar_t__ DEPRECATED_STREQN (char const*,char*,int) ; 
 char* TYPE_FIELD_NAME (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  check_typedef (struct type*) ; 

int
ada_is_parent_field (struct type *type, int field_num)
{
  const char *name = TYPE_FIELD_NAME (check_typedef (type), field_num);
  return (name != NULL &&
	  (DEPRECATED_STREQN (name, "PARENT", 6) || DEPRECATED_STREQN (name, "_parent", 7)));
}