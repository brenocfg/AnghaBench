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
struct TYPE_2__ {int /*<<< orphan*/  format; } ;

/* Variables and functions */
 unsigned int NUM_RTX_CODE ; 
 TYPE_1__* defs ; 
 char** formats ; 
 int /*<<< orphan*/  gendecl (char const*) ; 
 int /*<<< orphan*/  genmacro (unsigned int) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  special_format (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
genheader (void)
{
  unsigned int i;
  const char **fmt;

  puts ("#ifndef GCC_GENRTL_H");
  puts ("#define GCC_GENRTL_H\n");

  for (fmt = formats; *fmt; ++fmt)
    gendecl (*fmt);

  putchar ('\n');

  for (i = 0; i < NUM_RTX_CODE; i++)
    if (! special_format (defs[i].format))
      genmacro (i);

  puts ("\n#endif /* GCC_GENRTL_H */");
}