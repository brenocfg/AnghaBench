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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  rtx ;
typedef  int /*<<< orphan*/  diagnostic_t ;
typedef  int /*<<< orphan*/  diagnostic_info ;

/* Variables and functions */
 int /*<<< orphan*/  diagnostic_set_info (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  location_for_asm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  report_diagnostic (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
diagnostic_for_asm (rtx insn, const char *msg, va_list *args_ptr,
		    diagnostic_t kind)
{
  diagnostic_info diagnostic;

  diagnostic_set_info (&diagnostic, msg, args_ptr,
		       location_for_asm (insn), kind);
  report_diagnostic (&diagnostic);
}