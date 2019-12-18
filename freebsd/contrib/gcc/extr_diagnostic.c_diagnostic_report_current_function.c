#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  diagnostic_context ;
struct TYPE_2__ {int /*<<< orphan*/  (* print_error_function ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  diagnostic_report_current_module (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_filename ; 
 TYPE_1__ lang_hooks ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
diagnostic_report_current_function (diagnostic_context *context)
{
  diagnostic_report_current_module (context);
  lang_hooks.print_error_function (context, input_filename);
}