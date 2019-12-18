#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct regcache {TYPE_1__* descr; int /*<<< orphan*/  readonly_p; } ;
struct TYPE_2__ {int nr_raw_registers; int /*<<< orphan*/ * sizeof_register; scalar_t__ legacy_p; } ;

/* Variables and functions */
 struct regcache* current_regcache ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  legacy_read_register_gen (int,void*) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptid_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_buffer (struct regcache*,int) ; 
 int /*<<< orphan*/  register_cached (int) ; 
 int /*<<< orphan*/  registers_changed () ; 
 int /*<<< orphan*/  registers_ptid ; 
 int /*<<< orphan*/  target_fetch_registers (int) ; 

void
regcache_raw_read (struct regcache *regcache, int regnum, void *buf)
{
  gdb_assert (regcache != NULL && buf != NULL);
  gdb_assert (regnum >= 0 && regnum < regcache->descr->nr_raw_registers);
  if (regcache->descr->legacy_p
      && !regcache->readonly_p)
    {
      gdb_assert (regcache == current_regcache);
      /* For moment, just use underlying legacy code.  Ulgh!!! This
	 silently and very indirectly updates the regcache's regcache
	 via the global deprecated_register_valid[].  */
      legacy_read_register_gen (regnum, buf);
      return;
    }
  /* Make certain that the register cache is up-to-date with respect
     to the current thread.  This switching shouldn't be necessary
     only there is still only one target side register cache.  Sigh!
     On the bright side, at least there is a regcache object.  */
  if (!regcache->readonly_p)
    {
      gdb_assert (regcache == current_regcache);
      if (! ptid_equal (registers_ptid, inferior_ptid))
	{
	  registers_changed ();
	  registers_ptid = inferior_ptid;
	}
      if (!register_cached (regnum))
	target_fetch_registers (regnum);
    }
  /* Copy the value directly into the register cache.  */
  memcpy (buf, register_buffer (regcache, regnum),
	  regcache->descr->sizeof_register[regnum]);
}