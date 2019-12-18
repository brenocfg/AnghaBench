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
 int /*<<< orphan*/  Adp_CloseDevice () ; 
 int RDIError_NoError ; 
 int angel_RDI_close () ; 
 int closed_already ; 
 int /*<<< orphan*/  generic_mourn_inferior () ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  null_ptid ; 
 int /*<<< orphan*/  printf_filtered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdi_error_message (int) ; 

__attribute__((used)) static void
arm_rdi_close (int quitting)
{
  int rslt;

  if (!closed_already)
    {
      rslt = angel_RDI_close ();
      if (rslt != RDIError_NoError)
	{
	  printf_filtered ("RDI_close: %s\n", rdi_error_message (rslt));
	}
      closed_already = 1;
      inferior_ptid = null_ptid;
      Adp_CloseDevice ();
      generic_mourn_inferior ();
    }
}