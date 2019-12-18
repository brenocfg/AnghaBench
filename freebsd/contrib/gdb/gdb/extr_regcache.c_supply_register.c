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
 int /*<<< orphan*/  DEPRECATED_CLEAN_UP_REGISTER_VALUE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_regcache ; 
 int /*<<< orphan*/  regcache_raw_supply (int /*<<< orphan*/ ,int,void const*) ; 
 int /*<<< orphan*/  register_buffer (int /*<<< orphan*/ ,int) ; 

void
supply_register (int regnum, const void *val)
{
  regcache_raw_supply (current_regcache, regnum, val);

  /* On some architectures, e.g. HPPA, there are a few stray bits in
     some registers, that the rest of the code would like to ignore.  */

  /* NOTE: cagney/2001-03-16: The macro CLEAN_UP_REGISTER_VALUE is
     going to be deprecated.  Instead architectures will leave the raw
     register value as is and instead clean things up as they pass
     through the method gdbarch_pseudo_register_read() clean up the
     values. */

#ifdef DEPRECATED_CLEAN_UP_REGISTER_VALUE
  DEPRECATED_CLEAN_UP_REGISTER_VALUE \
    (regnum, register_buffer (current_regcache, regnum));
#endif
}