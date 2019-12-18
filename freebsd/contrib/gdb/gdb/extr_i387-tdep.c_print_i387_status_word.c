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
struct ui_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  fputs_filtered (char*,struct ui_file*) ; 
 unsigned int local_hex_string_custom (unsigned int,char*) ; 

__attribute__((used)) static void
print_i387_status_word (unsigned int status, struct ui_file *file)
{
  fprintf_filtered (file, "Status Word:         %s",
		   local_hex_string_custom (status, "04"));
  fputs_filtered ("  ", file);
  fprintf_filtered (file, " %s", (status & 0x0001) ? "IE" : "  ");
  fprintf_filtered (file, " %s", (status & 0x0002) ? "DE" : "  ");
  fprintf_filtered (file, " %s", (status & 0x0004) ? "ZE" : "  ");
  fprintf_filtered (file, " %s", (status & 0x0008) ? "OE" : "  ");
  fprintf_filtered (file, " %s", (status & 0x0010) ? "UE" : "  ");
  fprintf_filtered (file, " %s", (status & 0x0020) ? "PE" : "  ");
  fputs_filtered ("  ", file);
  fprintf_filtered (file, " %s", (status & 0x0080) ? "ES" : "  ");
  fputs_filtered ("  ", file);
  fprintf_filtered (file, " %s", (status & 0x0040) ? "SF" : "  ");
  fputs_filtered ("  ", file);
  fprintf_filtered (file, " %s", (status & 0x0100) ? "C0" : "  ");
  fprintf_filtered (file, " %s", (status & 0x0200) ? "C1" : "  ");
  fprintf_filtered (file, " %s", (status & 0x0400) ? "C2" : "  ");
  fprintf_filtered (file, " %s", (status & 0x4000) ? "C3" : "  ");

  fputs_filtered ("\n", file);

  fprintf_filtered (file,
		    "                       TOP: %d\n", ((status >> 11) & 7));
}