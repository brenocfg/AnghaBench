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
 struct type* ada_find_parallel_type (struct type*,char*) ; 
 int /*<<< orphan*/  ada_type_name (struct type*) ; 
 struct type* desc_base_type (struct type*) ; 
 scalar_t__ is_suffix (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct type *
thin_descriptor_type (struct type *type)
{
  struct type *base_type = desc_base_type (type);
  if (base_type == NULL)
    return NULL;
  if (is_suffix (ada_type_name (base_type), "___XVE"))
    return base_type;
  else
    {
      struct type *alt_type = ada_find_parallel_type (base_type, "___XVE");
      if (alt_type == NULL)
	return base_type;
      else
	return alt_type;
    }
}