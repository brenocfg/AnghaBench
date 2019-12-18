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
 int ocd_read_bytes (int /*<<< orphan*/ ,char*,int) ; 
 int ocd_write_bytes (int /*<<< orphan*/ ,char*,int) ; 

int
ocd_xfer_memory (CORE_ADDR memaddr, char *myaddr, int len, int should_write,
		 struct mem_attrib *attrib, struct target_ops *target)
{
  int res;

  if (should_write)
    res = ocd_write_bytes (memaddr, myaddr, len);
  else
    res = ocd_read_bytes (memaddr, myaddr, len);

  return res;
}