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
typedef  int /*<<< orphan*/  LONGEST ;

/* Variables and functions */
 int /*<<< orphan*/  GROW_VECT (char*,size_t,scalar_t__) ; 
 int /*<<< orphan*/  ada_print_scalar (struct type*,int /*<<< orphan*/ ,struct ui_file*) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*) ; 
 int /*<<< orphan*/  get_int_var_value (char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static void
print_dynamic_range_bound (struct type *type, const char *name, int name_len,
			   const char *suffix, struct ui_file *stream)
{
  static char *name_buf = NULL;
  static size_t name_buf_len = 0;
  LONGEST B;
  int OK;

  GROW_VECT (name_buf, name_buf_len, name_len + strlen (suffix) + 1);
  strncpy (name_buf, name, name_len);
  strcpy (name_buf + name_len, suffix);

  B = get_int_var_value (name_buf, 0, &OK);
  if (OK)
    ada_print_scalar (type, B, stream);
  else
    fprintf_filtered (stream, "?");
}