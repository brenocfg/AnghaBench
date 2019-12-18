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
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,char*) ; 
 int /*<<< orphan*/  fputs_filtered (char*,struct ui_file*) ; 
 char* local_hex_string_custom (unsigned int,char*) ; 

__attribute__((used)) static void
print_i387_control_word (unsigned int control, struct ui_file *file)
{
  fprintf_filtered (file, "Control Word:        %s",
		   local_hex_string_custom (control, "04"));
  fputs_filtered ("  ", file);
  fprintf_filtered (file, " %s", (control & 0x0001) ? "IM" : "  ");
  fprintf_filtered (file, " %s", (control & 0x0002) ? "DM" : "  ");
  fprintf_filtered (file, " %s", (control & 0x0004) ? "ZM" : "  ");
  fprintf_filtered (file, " %s", (control & 0x0008) ? "OM" : "  ");
  fprintf_filtered (file, " %s", (control & 0x0010) ? "UM" : "  ");
  fprintf_filtered (file, " %s", (control & 0x0020) ? "PM" : "  ");

  fputs_filtered ("\n", file);

  fputs_filtered ("                       PC: ", file);
  switch ((control >> 8) & 3)
    {
    case 0:
      fputs_filtered ("Single Precision (24-bits)\n", file);
      break;
    case 1:
      fputs_filtered ("Reserved\n", file);
      break;
    case 2:
      fputs_filtered ("Double Precision (53-bits)\n", file);
      break;
    case 3:
      fputs_filtered ("Extended Precision (64-bits)\n", file);
      break;
    }
      
  fputs_filtered ("                       RC: ", file);
  switch ((control >> 10) & 3)
    {
    case 0:
      fputs_filtered ("Round to nearest\n", file);
      break;
    case 1:
      fputs_filtered ("Round down\n", file);
      break;
    case 2:
      fputs_filtered ("Round up\n", file);
      break;
    case 3:
      fputs_filtered ("Round toward zero\n", file);
      break;
    }
}