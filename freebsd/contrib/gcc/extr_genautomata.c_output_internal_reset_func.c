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
 char* CHIP_NAME ; 
 char* CHIP_PARAMETER_NAME ; 
 char* INTERNAL_RESET_FUNC_NAME ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,...) ; 
 int /*<<< orphan*/  output_file ; 

__attribute__((used)) static void
output_internal_reset_func (void)
{
  fprintf (output_file, "static inline void\n%s (struct %s *%s)\n",
	   INTERNAL_RESET_FUNC_NAME, CHIP_NAME, CHIP_PARAMETER_NAME);
  fprintf (output_file, "{\n  memset (%s, 0, sizeof (struct %s));\n}\n\n",
	   CHIP_PARAMETER_NAME, CHIP_NAME);
}