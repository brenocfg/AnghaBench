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
 int RDIError_NoError ; 
 int angel_RDI_open (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdb_config ; 
 int /*<<< orphan*/  printf_filtered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdi_error_message (int) ; 

__attribute__((used)) static void
arm_rdi_kill (void)
{
  int rslt;

  rslt = angel_RDI_open (1, &gdb_config, NULL, NULL);
  if (rslt != RDIError_NoError)
    {
      printf_filtered ("RDI_open: %s\n", rdi_error_message (rslt));
    }
}