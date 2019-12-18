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
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_STRUCT ; 
 int /*<<< orphan*/ * bound_name ; 
 struct type* desc_base_type (struct type*) ; 
 struct type* lookup_struct_elt_type (struct type*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct type *
desc_index_type (struct type *type, int i)
{
  type = desc_base_type (type);

  if (TYPE_CODE (type) == TYPE_CODE_STRUCT)
    return lookup_struct_elt_type (type, bound_name[2 * i - 2], 1);
  else
    return NULL;
}