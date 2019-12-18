#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  printer; } ;
typedef  TYPE_1__ diagnostic_context ;

/* Variables and functions */
 int /*<<< orphan*/  lhd_print_error_function (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  maybe_print_instantiation_context (TYPE_1__*) ; 
 int /*<<< orphan*/  pp_base_set_prefix (int /*<<< orphan*/ ,char const*) ; 

void
cxx_print_error_function (diagnostic_context *context, const char *file)
{
  lhd_print_error_function (context, file);
  pp_base_set_prefix (context->printer, file);
  maybe_print_instantiation_context (context);
}