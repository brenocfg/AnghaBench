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
 scalar_t__ TYPE_CODE_ENUM ; 
 int TYPE_FLAGS (struct type*) ; 
 int TYPE_FLAG_STUB ; 
 char* TYPE_TAG_NAME (struct type*) ; 
 struct type* ada_find_any_type (char*) ; 

struct type *
ada_completed_type (struct type *type)
{
  CHECK_TYPEDEF (type);
  if (type == NULL || TYPE_CODE (type) != TYPE_CODE_ENUM
      || (TYPE_FLAGS (type) & TYPE_FLAG_STUB) == 0
      || TYPE_TAG_NAME (type) == NULL)
    return type;
  else
    {
      char *name = TYPE_TAG_NAME (type);
      struct type *type1 = ada_find_any_type (name);
      return (type1 == NULL) ? type : type1;
    }
}