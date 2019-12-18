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
 char** formats ; 
 int /*<<< orphan*/  gendef (char const*) ; 
 int /*<<< orphan*/  puts (char*) ; 

__attribute__((used)) static void
gencode (void)
{
  const char **fmt;

  puts ("#include \"config.h\"");
  puts ("#include \"system.h\"");
  puts ("#include \"coretypes.h\"");
  puts ("#include \"tm.h\"");
  puts ("#include \"obstack.h\"");
  puts ("#include \"rtl.h\"");
  puts ("#include \"ggc.h\"\n");

  for (fmt = formats; *fmt != 0; fmt++)
    gendef (*fmt);
}