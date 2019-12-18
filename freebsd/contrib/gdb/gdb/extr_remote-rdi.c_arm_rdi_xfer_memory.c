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
struct mem_attrib {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int RDIError_NoError ; 
 int angel_RDI_read (int /*<<< orphan*/ ,char*,int*) ; 
 int angel_RDI_write (char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  printf_filtered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdi_error_message (int) ; 

__attribute__((used)) static int
arm_rdi_xfer_memory (CORE_ADDR memaddr, char *myaddr, int len,
		     int should_write, struct mem_attrib *attrib,
		     struct target_ops *target)
{
  int rslt, i;

  if (should_write)
    {
      rslt = angel_RDI_write (myaddr, memaddr, &len);
      if (rslt != RDIError_NoError)
	{
	  printf_filtered ("RDI_write: %s\n", rdi_error_message (rslt));
	}
    }
  else
    {
      rslt = angel_RDI_read (memaddr, myaddr, &len);
      if (rslt != RDIError_NoError)
	{
	  printf_filtered ("RDI_read: %s\n", rdi_error_message (rslt));
	  len = 0;
	}
    }
  return len;
}