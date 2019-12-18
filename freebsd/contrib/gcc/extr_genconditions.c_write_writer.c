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
 int /*<<< orphan*/  puts (char*) ; 

__attribute__((used)) static void
write_writer (void)
{
  puts ("int\n"
	"main(void)\n"
	"{\n"
	"  unsigned int i;\n"
        "  const char *p;\n"
        "  puts (\"(define_conditions [\");\n"
	"#if GCC_VERSION >= 3001\n"
	"  for (i = 0; i < ARRAY_SIZE (insn_conditions); i++)\n"
	"    {\n"
	"      printf (\"  (%d \\\"\", insn_conditions[i].value);\n"
	"      for (p = insn_conditions[i].expr; *p; p++)\n"
	"        {\n"
	"          switch (*p)\n"
	"	     {\n"
	"	     case '\\\\':\n"
	"	     case '\\\"': putchar ('\\\\'); break;\n"
	"	     default: break;\n"
	"	     }\n"
	"          putchar (*p);\n"
	"        }\n"
        "      puts (\"\\\")\");\n"
        "    }\n"
	"#endif /* gcc >= 3.0.1 */\n"
	"  puts (\"])\");\n"
        "  fflush (stdout);\n"
        "return ferror (stdout) != 0 ? FATAL_EXIT_CODE : SUCCESS_EXIT_CODE;\n"
	"}");
}