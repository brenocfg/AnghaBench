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
struct gdbarch {int dummy; } ;
struct frame_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_FPS_REGNUM ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_fpu_flags (unsigned long) ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 unsigned long read_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
arm_print_float_info (struct gdbarch *gdbarch, struct ui_file *file,
		      struct frame_info *frame, const char *args)
{
  unsigned long status = read_register (ARM_FPS_REGNUM);
  int type;

  type = (status >> 24) & 127;
  printf ("%s FPU type %d\n",
	  (status & (1 << 31)) ? "Hardware" : "Software",
	  type);
  fputs ("mask: ", stdout);
  print_fpu_flags (status >> 16);
  fputs ("flags: ", stdout);
  print_fpu_flags (status);
}