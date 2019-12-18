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
 int ada_array_arity (struct type*) ; 
 struct type* ada_array_element_type (struct type*,int) ; 
 scalar_t__ ada_is_array_descriptor (struct type*) ; 
 int ada_is_character_type (struct type*) ; 
 scalar_t__ ada_is_simple_array (struct type*) ; 

int
ada_is_string_type (struct type *type)
{
  CHECK_TYPEDEF (type);
  if (type != NULL
      && TYPE_CODE (type) != TYPE_CODE_PTR
      && (ada_is_simple_array (type) || ada_is_array_descriptor (type))
      && ada_array_arity (type) == 1)
    {
      struct type *elttype = ada_array_element_type (type, 1);

      return ada_is_character_type (elttype);
    }
  else
    return 0;
}