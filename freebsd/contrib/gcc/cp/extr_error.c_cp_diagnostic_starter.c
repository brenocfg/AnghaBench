#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  diagnostic_info ;
struct TYPE_6__ {int /*<<< orphan*/  printer; } ;
typedef  TYPE_1__ diagnostic_context ;

/* Variables and functions */
 int /*<<< orphan*/  cp_print_error_function (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  diagnostic_build_prefix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  diagnostic_report_current_module (TYPE_1__*) ; 
 int /*<<< orphan*/  maybe_print_instantiation_context (TYPE_1__*) ; 
 int /*<<< orphan*/  pp_base_set_prefix (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cp_diagnostic_starter (diagnostic_context *context,
		       diagnostic_info *diagnostic)
{
  diagnostic_report_current_module (context);
  cp_print_error_function (context, diagnostic);
  maybe_print_instantiation_context (context);
  pp_base_set_prefix (context->printer, diagnostic_build_prefix (diagnostic));
}