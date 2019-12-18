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
 struct type* ada_lookup_struct_elt_type (struct type*,char*,int,int /*<<< orphan*/ *) ; 
 char* ada_variant_discrim_name (struct type*) ; 
 struct type* builtin_type_int ; 

struct type *
ada_variant_discrim_type (struct type *var_type, struct type *outer_type)
{
  char *name = ada_variant_discrim_name (var_type);
  struct type *type = ada_lookup_struct_elt_type (outer_type, name, 1, NULL);
  if (type == NULL)
    return builtin_type_int;
  else
    return type;
}