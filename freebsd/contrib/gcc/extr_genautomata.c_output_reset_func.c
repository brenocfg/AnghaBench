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

/* Variables and functions */
 char* INTERNAL_RESET_FUNC_NAME ; 
 char* RESET_FUNC_NAME ; 
 char* STATE_NAME ; 
 char* STATE_TYPE_NAME ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,...) ; 
 int /*<<< orphan*/  output_file ; 

__attribute__((used)) static void
output_reset_func (void)
{
  fprintf (output_file, "void\n%s (%s %s)\n",
	   RESET_FUNC_NAME, STATE_TYPE_NAME, STATE_NAME);
  fprintf (output_file, "{\n  %s (%s);\n}\n\n", INTERNAL_RESET_FUNC_NAME,
	   STATE_NAME);
}