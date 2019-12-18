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
 int st2000_read_inferior_memory (int /*<<< orphan*/ ,char*,int) ; 
 int st2000_write_inferior_memory (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
st2000_xfer_inferior_memory (CORE_ADDR memaddr, char *myaddr, int len,
			     int write, struct mem_attrib *attrib,
			     struct target_ops *target)
{
  if (write)
    return st2000_write_inferior_memory (memaddr, myaddr, len);
  else
    return st2000_read_inferior_memory (memaddr, myaddr, len);
}