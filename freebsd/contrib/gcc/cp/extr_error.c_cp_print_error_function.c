#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  location; } ;
typedef  TYPE_1__ diagnostic_info ;
struct TYPE_13__ {TYPE_3__* printer; } ;
typedef  TYPE_2__ diagnostic_context ;
struct TYPE_14__ {char* prefix; } ;

/* Variables and functions */
 char* LOCATION_FILE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * current_function_decl ; 
 int /*<<< orphan*/  cxx_printable_name (int /*<<< orphan*/ *,int) ; 
 scalar_t__ diagnostic_last_function_changed (TYPE_2__*) ; 
 int /*<<< orphan*/  diagnostic_set_last_function (TYPE_2__*) ; 
 char* file_name_as_prefix (char const*) ; 
 int /*<<< orphan*/  function_category (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_base_destroy_prefix (TYPE_3__*) ; 
 int /*<<< orphan*/  pp_base_newline (TYPE_3__*) ; 
 int /*<<< orphan*/  pp_base_set_prefix (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  pp_base_string (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  pp_printf (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cp_print_error_function (diagnostic_context *context,
			 diagnostic_info *diagnostic)
{
  if (diagnostic_last_function_changed (context))
    {
      const char *old_prefix = context->printer->prefix;
      const char *file = LOCATION_FILE (diagnostic->location);
      char *new_prefix = file ? file_name_as_prefix (file) : NULL;

      pp_base_set_prefix (context->printer, new_prefix);

      if (current_function_decl == NULL)
	pp_base_string (context->printer, "At global scope:");
      else
	pp_printf (context->printer, "In %s %qs:",
		   function_category (current_function_decl),
		   cxx_printable_name (current_function_decl, 2));
      pp_base_newline (context->printer);

      diagnostic_set_last_function (context);
      pp_base_destroy_prefix (context->printer);
      context->printer->prefix = old_prefix;
    }
}