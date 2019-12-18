#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mapping {struct map_value* values; } ;
struct map_value {int dummy; } ;
struct TYPE_4__ {int num_builtins; void* attrs; int /*<<< orphan*/  apply_macro; int /*<<< orphan*/  uses_macro_p; int /*<<< orphan*/  find_builtin; void* macros; } ;

/* Variables and functions */
 char* GET_MODE_NAME (int) ; 
 char* GET_RTX_NAME (int) ; 
 int MAX_MACHINE_MODE ; 
 int NUM_RTX_CODE ; 
 char TOLOWER (char) ; 
 char TOUPPER (char) ; 
 struct map_value** add_map_value (struct map_value**,int,char*) ; 
 struct mapping* add_mapping (TYPE_1__*,void*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apply_code_macro ; 
 int /*<<< orphan*/  apply_mode_macro ; 
 TYPE_1__ codes ; 
 int /*<<< orphan*/  def_hash ; 
 int /*<<< orphan*/  def_name_eq_p ; 
 int /*<<< orphan*/  find_code ; 
 int /*<<< orphan*/  find_mode ; 
 void* htab_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ modes ; 
 int /*<<< orphan*/  uses_code_macro_p ; 
 int /*<<< orphan*/  uses_mode_macro_p ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static void
initialize_macros (void)
{
  struct mapping *lower, *upper;
  struct map_value **lower_ptr, **upper_ptr;
  char *copy, *p;
  int i;

  modes.attrs = htab_create (13, def_hash, def_name_eq_p, 0);
  modes.macros = htab_create (13, def_hash, def_name_eq_p, 0);
  modes.num_builtins = MAX_MACHINE_MODE;
  modes.find_builtin = find_mode;
  modes.uses_macro_p = uses_mode_macro_p;
  modes.apply_macro = apply_mode_macro;

  codes.attrs = htab_create (13, def_hash, def_name_eq_p, 0);
  codes.macros = htab_create (13, def_hash, def_name_eq_p, 0);
  codes.num_builtins = NUM_RTX_CODE;
  codes.find_builtin = find_code;
  codes.uses_macro_p = uses_code_macro_p;
  codes.apply_macro = apply_code_macro;

  lower = add_mapping (&modes, modes.attrs, "mode", 0);
  upper = add_mapping (&modes, modes.attrs, "MODE", 0);
  lower_ptr = &lower->values;
  upper_ptr = &upper->values;
  for (i = 0; i < MAX_MACHINE_MODE; i++)
    {
      copy = xstrdup (GET_MODE_NAME (i));
      for (p = copy; *p != 0; p++)
	*p = TOLOWER (*p);

      upper_ptr = add_map_value (upper_ptr, i, GET_MODE_NAME (i));
      lower_ptr = add_map_value (lower_ptr, i, copy);
    }

  lower = add_mapping (&codes, codes.attrs, "code", 0);
  upper = add_mapping (&codes, codes.attrs, "CODE", 0);
  lower_ptr = &lower->values;
  upper_ptr = &upper->values;
  for (i = 0; i < NUM_RTX_CODE; i++)
    {
      copy = xstrdup (GET_RTX_NAME (i));
      for (p = copy; *p != 0; p++)
	*p = TOUPPER (*p);

      lower_ptr = add_map_value (lower_ptr, i, GET_RTX_NAME (i));
      upper_ptr = add_map_value (upper_ptr, i, copy);
    }
}