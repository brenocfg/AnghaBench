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
typedef  int /*<<< orphan*/  procinfo ;

/* Variables and functions */
 int TARGET_PTR_BIT ; 
 int /*<<< orphan*/  info_mappings_callback ; 
 int /*<<< orphan*/  iterate_over_mappings (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 

__attribute__((used)) static void
info_proc_mappings (procinfo *pi, int summary)
{
  char *header_fmt_string;

  if (TARGET_PTR_BIT == 32)
    header_fmt_string = "\t%10s %10s %10s %10s %7s\n";
  else
    header_fmt_string = "  %18s %18s %10s %10s %7s\n";

  if (summary)
    return;	/* No output for summary mode. */

  printf_filtered ("Mapped address spaces:\n\n");
  printf_filtered (header_fmt_string,
		   "Start Addr",
		   "  End Addr",
		   "      Size",
		   "    Offset",
		   "Flags");

  iterate_over_mappings (pi, NULL, NULL, info_mappings_callback);
  printf_filtered ("\n");
}