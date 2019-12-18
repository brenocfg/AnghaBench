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
 scalar_t__ TYPE_CODE_PTR ; 
 int /*<<< orphan*/  TYPE_TARGET_TYPE (struct type*) ; 
 struct type* check_typedef (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct type *
desc_base_type (struct type *type)
{
  if (type == NULL)
    return NULL;
  CHECK_TYPEDEF (type);
  if (type != NULL && TYPE_CODE (type) == TYPE_CODE_PTR)
    return check_typedef (TYPE_TARGET_TYPE (type));
  else
    return type;
}