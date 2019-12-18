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
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_STRUCT ; 
 int /*<<< orphan*/  TYPE_FIELD_TYPE (struct type*,int) ; 
 int TYPE_NFIELDS (struct type*) ; 
 scalar_t__ ada_is_parent_field (struct type*,int) ; 
 struct type* check_typedef (int /*<<< orphan*/ ) ; 

struct type *
ada_parent_type (struct type *type)
{
  int i;

  CHECK_TYPEDEF (type);

  if (type == NULL || TYPE_CODE (type) != TYPE_CODE_STRUCT)
    return NULL;

  for (i = 0; i < TYPE_NFIELDS (type); i += 1)
    if (ada_is_parent_field (type, i))
      return check_typedef (TYPE_FIELD_TYPE (type, i));

  return NULL;
}