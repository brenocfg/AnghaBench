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
typedef  int /*<<< orphan*/  LONGEST ;

/* Variables and functions */
 int TYPE_NFIELDS (struct type*) ; 
 scalar_t__ ada_in_variant (int /*<<< orphan*/ ,struct type*,int) ; 
 scalar_t__ ada_is_others_clause (struct type*,int) ; 
 struct type* ada_lookup_struct_elt_type (struct type*,char*,int,int*) ; 
 char* ada_variant_discrim_name (struct type*) ; 
 int /*<<< orphan*/  unpack_long (struct type*,char*) ; 

int
ada_which_variant_applies (struct type *var_type, struct type *outer_type,
			   char *outer_valaddr)
{
  int others_clause;
  int i;
  int disp;
  struct type *discrim_type;
  char *discrim_name = ada_variant_discrim_name (var_type);
  LONGEST discrim_val;

  disp = 0;
  discrim_type =
    ada_lookup_struct_elt_type (outer_type, discrim_name, 1, &disp);
  if (discrim_type == NULL)
    return -1;
  discrim_val = unpack_long (discrim_type, outer_valaddr + disp);

  others_clause = -1;
  for (i = 0; i < TYPE_NFIELDS (var_type); i += 1)
    {
      if (ada_is_others_clause (var_type, i))
	others_clause = i;
      else if (ada_in_variant (discrim_val, var_type, i))
	return i;
    }

  return others_clause;
}