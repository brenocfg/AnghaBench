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
struct target_ops {int dummy; } ;

/* Variables and functions */
 int RDIError_NoError ; 
 int /*<<< orphan*/  RDIInfo_Icebreaker ; 
 int /*<<< orphan*/  RDIInfo_Step ; 
 int /*<<< orphan*/  RDIInfo_Target ; 
 int angel_RDI_info (int /*<<< orphan*/ ,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  rdi_error_message (int) ; 

__attribute__((used)) static void
arm_rdi_files_info (struct target_ops *ignore)
{
  char *file = "nothing";
  int rslt;
  unsigned long arg1, arg2;

  rslt = angel_RDI_info (RDIInfo_Target, &arg1, &arg2);
  if (rslt != RDIError_NoError)
    {
      printf_filtered ("RDI_info: %s\n", rdi_error_message (rslt));
    }
  if (arg1 & (1 << 15))
    printf_filtered ("Target supports Thumb code.\n");
  if (arg1 & (1 << 14))
    printf_filtered ("Target can do profiling.\n");
  if (arg1 & (1 << 4))
    printf_filtered ("Target is real hardware.\n");

  rslt = angel_RDI_info (RDIInfo_Step, &arg1, &arg2);
  if (rslt != RDIError_NoError)
    {
      printf_filtered ("RDI_info: %s\n", rdi_error_message (rslt));
    }
  printf_filtered ("Target can%s single-step.\n", (arg1 & 0x4 ? "" : "not"));

  rslt = angel_RDI_info (RDIInfo_Icebreaker, &arg1, &arg2);
  if (rslt != RDIError_NoError)
    {
      printf_filtered ("RDI_info: %s\n", rdi_error_message (rslt));
    }
  else
    printf_filtered ("Target includes an EmbeddedICE.\n");
}