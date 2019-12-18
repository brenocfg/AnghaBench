#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* descr; } ;
struct TYPE_4__ {scalar_t__ gdbarch; scalar_t__ legacy_p; } ;

/* Variables and functions */
 scalar_t__ current_gdbarch ; 
 TYPE_2__* current_regcache ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  legacy_read_register_gen (int,char*) ; 
 int /*<<< orphan*/  regcache_cooked_read (TYPE_2__*,int,char*) ; 

void
deprecated_read_register_gen (int regnum, char *buf)
{
  gdb_assert (current_regcache != NULL);
  gdb_assert (current_regcache->descr->gdbarch == current_gdbarch);
  if (current_regcache->descr->legacy_p)
    {
      legacy_read_register_gen (regnum, buf);
      return;
    }
  regcache_cooked_read (current_regcache, regnum, buf);
}