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
struct regcache {int* register_valid_p; TYPE_1__* descr; int /*<<< orphan*/  readonly_p; } ;
struct TYPE_2__ {int nr_raw_registers; int /*<<< orphan*/ * sizeof_register; scalar_t__ legacy_p; } ;

/* Variables and functions */
 scalar_t__ CANNOT_STORE_REGISTER (int) ; 
 struct regcache* current_regcache ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  legacy_write_register_gen (int,void const*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptid_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ regcache_valid_p (struct regcache*,int) ; 
 int /*<<< orphan*/  register_buffer (struct regcache*,int) ; 
 int /*<<< orphan*/  registers_changed () ; 
 int /*<<< orphan*/  registers_ptid ; 
 int /*<<< orphan*/  target_prepare_to_store () ; 
 int /*<<< orphan*/  target_store_registers (int) ; 

void
regcache_raw_write (struct regcache *regcache, int regnum, const void *buf)
{
  gdb_assert (regcache != NULL && buf != NULL);
  gdb_assert (regnum >= 0 && regnum < regcache->descr->nr_raw_registers);
  gdb_assert (!regcache->readonly_p);

  if (regcache->descr->legacy_p)
    {
      /* For moment, just use underlying legacy code.  Ulgh!!! This
	 silently and very indirectly updates the regcache's buffers
	 via the globals deprecated_register_valid[] and registers[].  */
      gdb_assert (regcache == current_regcache);
      legacy_write_register_gen (regnum, buf);
      return;
    }

  /* On the sparc, writing %g0 is a no-op, so we don't even want to
     change the registers array if something writes to this register.  */
  if (CANNOT_STORE_REGISTER (regnum))
    return;

  /* Make certain that the correct cache is selected.  */
  gdb_assert (regcache == current_regcache);
  if (! ptid_equal (registers_ptid, inferior_ptid))
    {
      registers_changed ();
      registers_ptid = inferior_ptid;
    }

  /* If we have a valid copy of the register, and new value == old
     value, then don't bother doing the actual store. */
  if (regcache_valid_p (regcache, regnum)
      && (memcmp (register_buffer (regcache, regnum), buf,
		  regcache->descr->sizeof_register[regnum]) == 0))
    return;

  target_prepare_to_store ();
  memcpy (register_buffer (regcache, regnum), buf,
	  regcache->descr->sizeof_register[regnum]);
  regcache->register_valid_p[regnum] = 1;
  target_store_registers (regnum);
}