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
struct regcache {int dummy; } ;
typedef  int /*<<< orphan*/  ULONGEST ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 struct regcache* deprecated_find_dummy_frame_regcache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_cooked_read_unsigned (struct regcache*,int,int /*<<< orphan*/ *) ; 

CORE_ADDR
deprecated_read_register_dummy (CORE_ADDR pc, CORE_ADDR fp, int regno)
{
  struct regcache *dummy_regs = deprecated_find_dummy_frame_regcache (pc, fp);

  if (dummy_regs)
    {
      /* NOTE: cagney/2002-08-12: Replaced a call to
	 regcache_raw_read_as_address() with a call to
	 regcache_cooked_read_unsigned().  The old, ...as_address
	 function was eventually calling extract_unsigned_integer (nee
	 extract_address) to unpack the registers value.  The below is
	 doing an unsigned extract so that it is functionally
	 equivalent.  The read needs to be cooked as, otherwise, it
	 will never correctly return the value of a register in the
	 [NUM_REGS .. NUM_REGS+NUM_PSEUDO_REGS) range.  */
      ULONGEST val;
      regcache_cooked_read_unsigned (dummy_regs, regno, &val);
      return val;
    }
  else
    return 0;
}