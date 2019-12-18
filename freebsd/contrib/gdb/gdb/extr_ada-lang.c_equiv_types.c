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
 scalar_t__ DEPRECATED_STREQ (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_ENUM ; 
 scalar_t__ TYPE_CODE_STRUCT ; 
 int /*<<< orphan*/ * ada_type_name (struct type*) ; 

__attribute__((used)) static int
equiv_types (struct type *type0, struct type *type1)
{
  if (type0 == type1)
    return 1;
  if (type0 == NULL || type1 == NULL
      || TYPE_CODE (type0) != TYPE_CODE (type1))
    return 0;
  if ((TYPE_CODE (type0) == TYPE_CODE_STRUCT
       || TYPE_CODE (type0) == TYPE_CODE_ENUM)
      && ada_type_name (type0) != NULL && ada_type_name (type1) != NULL
      && DEPRECATED_STREQ (ada_type_name (type0), ada_type_name (type1)))
    return 1;

  return 0;
}