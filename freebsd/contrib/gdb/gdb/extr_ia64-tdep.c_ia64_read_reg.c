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
typedef  scalar_t__ ULONGEST ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  IA64_BSPSTORE_REGNUM ; 
 int /*<<< orphan*/  IA64_BSP_REGNUM ; 
 int /*<<< orphan*/  TARGET_OBJECT_DIRTY ; 
 int /*<<< orphan*/  current_regcache ; 
 int /*<<< orphan*/  current_target ; 
 int /*<<< orphan*/  read_memory (scalar_t__,void*,int) ; 
 int /*<<< orphan*/  regcache_cooked_read_unsigned (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  target_read_partial (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,void*,scalar_t__,int) ; 

__attribute__((used)) static void
ia64_read_reg (CORE_ADDR addr, void *buf, int len)
{
  ULONGEST bspstore;
  regcache_cooked_read_unsigned (current_regcache, IA64_BSPSTORE_REGNUM,
				 &bspstore);
  if (addr >= bspstore)
    {
      ULONGEST bsp;
      regcache_cooked_read_unsigned (current_regcache, IA64_BSP_REGNUM,
				     &bsp);
      if (addr < bsp)
	{
	  target_read_partial (&current_target, TARGET_OBJECT_DIRTY,
			       (void*)&bspstore, buf, addr - bspstore, len);
	  return;
	}
    }
  read_memory (addr, buf, len);
}