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
 int e7000_read_inferior_memory (int /*<<< orphan*/ ,char*,int) ; 
 int e7000_read_inferior_memory_large (int /*<<< orphan*/ ,char*,int) ; 
 int e7000_write_inferior_memory (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
e7000_xfer_inferior_memory (CORE_ADDR memaddr, char *myaddr, int len,
			    int write, struct mem_attrib *attrib,
			    struct target_ops *target)
{
  if (write)
    return e7000_write_inferior_memory (memaddr, myaddr, len);
  else if (len < 16)
    return e7000_read_inferior_memory (memaddr, myaddr, len);
  else
    return e7000_read_inferior_memory_large (memaddr, myaddr, len);
}