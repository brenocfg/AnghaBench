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
typedef  int /*<<< orphan*/  diagnostic_info ;
struct TYPE_4__ {int /*<<< orphan*/  printer; } ;
typedef  TYPE_1__ diagnostic_context ;

/* Variables and functions */
 int /*<<< orphan*/  diagnostic_build_prefix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  diagnostic_report_current_function (TYPE_1__*) ; 
 int /*<<< orphan*/  pp_set_prefix (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
default_diagnostic_starter (diagnostic_context *context,
			    diagnostic_info *diagnostic)
{
  diagnostic_report_current_function (context);
  pp_set_prefix (context->printer, diagnostic_build_prefix (diagnostic));
}