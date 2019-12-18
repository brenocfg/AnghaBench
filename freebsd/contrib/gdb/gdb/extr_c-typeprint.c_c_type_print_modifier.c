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
struct ui_file {int dummy; } ;
struct type {int dummy; } ;

/* Variables and functions */
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_REF ; 
 scalar_t__ TYPE_CONST (struct type*) ; 
 int /*<<< orphan*/  TYPE_INSTANCE_FLAGS (struct type*) ; 
 scalar_t__ TYPE_VOLATILE (struct type*) ; 
 char* address_space_int_to_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 

__attribute__((used)) static void
c_type_print_modifier (struct type *type, struct ui_file *stream,
		       int need_pre_space, int need_post_space)
{
  int did_print_modifier = 0;
  const char *address_space_id;

  /* We don't print `const' qualifiers for references --- since all
     operators affect the thing referenced, not the reference itself,
     every reference is `const'.  */
  if (TYPE_CONST (type)
      && TYPE_CODE (type) != TYPE_CODE_REF)
    {
      if (need_pre_space)
	fprintf_filtered (stream, " ");
      fprintf_filtered (stream, "const");
      did_print_modifier = 1;
    }

  if (TYPE_VOLATILE (type))
    {
      if (did_print_modifier || need_pre_space)
	fprintf_filtered (stream, " ");
      fprintf_filtered (stream, "volatile");
      did_print_modifier = 1;
    }

  address_space_id = address_space_int_to_name (TYPE_INSTANCE_FLAGS (type));
  if (address_space_id)
    {
      if (did_print_modifier || need_pre_space)
	fprintf_filtered (stream, " ");
      fprintf_filtered (stream, "@%s", address_space_id);
      did_print_modifier = 1;
    }

  if (did_print_modifier && need_post_space)
    fprintf_filtered (stream, " ");
}