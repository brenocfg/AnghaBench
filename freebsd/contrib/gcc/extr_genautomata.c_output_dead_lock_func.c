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
 char* DEAD_LOCK_FUNC_NAME ; 
 char* INTERNAL_DEAD_LOCK_FUNC_NAME ; 
 char* STATE_NAME ; 
 char* STATE_TYPE_NAME ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,...) ; 
 int /*<<< orphan*/  output_file ; 

__attribute__((used)) static void
output_dead_lock_func (void)
{
  fprintf (output_file, "int\n%s (%s %s)\n",
	   DEAD_LOCK_FUNC_NAME, STATE_TYPE_NAME, STATE_NAME);
  fprintf (output_file, "{\n  return %s (%s);\n}\n\n",
	   INTERNAL_DEAD_LOCK_FUNC_NAME, STATE_NAME);
}