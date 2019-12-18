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
 int /*<<< orphan*/  AR_EMUL_USAGE_PRINT_OPTION_HEADER (int /*<<< orphan*/ *) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 

void
ar_emul_default_usage (FILE *fp)
{
  AR_EMUL_USAGE_PRINT_OPTION_HEADER (fp);
  /* xgettext:c-format */
  fprintf (fp, _("  No emulation specific options\n"));
}