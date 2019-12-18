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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  outf ; 
 scalar_t__ partial_count ; 

__attribute__((used)) static void
write_lbrac (void)
{
  if (partial_count)
    {
      fprintf (outf, "#ifndef _PARAMS\n");
      fprintf (outf, "#if defined(__STDC__) || defined(__cplusplus)\n");
      fprintf (outf, "#define _PARAMS(ARGS) ARGS\n");
      fprintf (outf, "#else\n");
      fprintf (outf, "#define _PARAMS(ARGS) ()\n");
      fprintf (outf, "#endif\n#endif /* _PARAMS */\n");
    }
}