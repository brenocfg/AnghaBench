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
struct TYPE_2__ {int nr_raw_registers; size_t* sizeof_register; } ;

/* Variables and functions */
 struct regcache* current_regcache ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ptid_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* register_buffer (struct regcache*,int) ; 
 int /*<<< orphan*/  registers_changed () ; 
 int /*<<< orphan*/  registers_ptid ; 

void
regcache_raw_supply (struct regcache *regcache, int regnum, const void *buf)
{
  void *regbuf;
  size_t size;

  gdb_assert (regcache != NULL);
  gdb_assert (regnum >= 0 && regnum < regcache->descr->nr_raw_registers);
  gdb_assert (!regcache->readonly_p);

  /* FIXME: kettenis/20030828: It shouldn't be necessary to handle
     CURRENT_REGCACHE specially here.  */
  if (regcache == current_regcache
      && !ptid_equal (registers_ptid, inferior_ptid))
    {
      registers_changed ();
      registers_ptid = inferior_ptid;
    }

  regbuf = register_buffer (regcache, regnum);
  size = regcache->descr->sizeof_register[regnum];

  if (buf)
    memcpy (regbuf, buf, size);
  else
    memset (regbuf, 0, size);

  /* Mark the register as cached.  */
  regcache->register_valid_p[regnum] = 1;
}