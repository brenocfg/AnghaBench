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
 int /*<<< orphan*/ * ada_lookup_struct_elt_type (struct type*,char*,int,int /*<<< orphan*/ *) ; 

int
ada_is_tagged_type (struct type *type)
{
  if (type == NULL || TYPE_CODE (type) != TYPE_CODE_STRUCT)
    return 0;

  return (ada_lookup_struct_elt_type (type, "_tag", 1, NULL) != NULL);
}