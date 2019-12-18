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
 scalar_t__ read_child (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ write_child (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
go32_xfer_memory (CORE_ADDR memaddr, char *myaddr, int len, int write,
		  struct mem_attrib *attrib, struct target_ops *target)
{
  if (write)
    {
      if (write_child (memaddr, myaddr, len))
	{
	  return 0;
	}
      else
	{
	  return len;
	}
    }
  else
    {
      if (read_child (memaddr, myaddr, len))
	{
	  return 0;
	}
      else
	{
	  return len;
	}
    }
}