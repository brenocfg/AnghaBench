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
 char* SIZE_FUNC_NAME ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  output_file ; 

__attribute__((used)) static void
output_size_func (void)
{
  fprintf (output_file, "int\n%s (void)\n", SIZE_FUNC_NAME);
  fprintf (output_file, "{\n  return sizeof (struct %s);\n}\n\n", CHIP_NAME);
}