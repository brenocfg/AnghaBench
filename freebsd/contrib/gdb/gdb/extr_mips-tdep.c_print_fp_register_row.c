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
struct frame_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*) ; 
 int /*<<< orphan*/  mips_print_fp_register (struct ui_file*,struct frame_info*,int) ; 

__attribute__((used)) static int
print_fp_register_row (struct ui_file *file, struct frame_info *frame,
		       int regnum)
{
  fprintf_filtered (file, " ");
  mips_print_fp_register (file, frame, regnum);
  fprintf_filtered (file, "\n");
  return regnum + 1;
}