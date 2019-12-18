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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
md_show_usage (FILE *stream)
{
  fputs (_("\
Alpha options:\n\
-32addr			treat addresses as 32-bit values\n\
-F			lack floating point instructions support\n\
-mev4 | -mev45 | -mev5 | -mev56 | -mpca56 | -mev6 | -mev67 | -mev68 | -mall\n\
			specify variant of Alpha architecture\n\
-m21064 | -m21066 | -m21164 | -m21164a | -m21164pc | -m21264 | -m21264a | -m21264b\n\
			these variants include PALcode opcodes\n"),
	stream);
#ifdef OBJ_EVAX
  fputs (_("\
VMS options:\n\
-+			hash encode (don't truncate) names longer than 64 characters\n\
-H			show new symbol after hash truncation\n"),
	stream);
#endif
}