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
struct gdbarch {int dummy; } ;

/* Variables and functions */
 int MAX_REGISTER_SIZE ; 
 scalar_t__ i386_mmx_regnum_p (struct gdbarch*,int) ; 
 int i386_mmx_regnum_to_fp_regnum (struct regcache*,int) ; 
 int /*<<< orphan*/  memcpy (char*,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_raw_read (struct regcache*,int,char*) ; 
 int /*<<< orphan*/  regcache_raw_write (struct regcache*,int,void const*) ; 
 int /*<<< orphan*/  register_size (struct gdbarch*,int) ; 

__attribute__((used)) static void
i386_pseudo_register_write (struct gdbarch *gdbarch, struct regcache *regcache,
			    int regnum, const void *buf)
{
  if (i386_mmx_regnum_p (gdbarch, regnum))
    {
      char mmx_buf[MAX_REGISTER_SIZE];
      int fpnum = i386_mmx_regnum_to_fp_regnum (regcache, regnum);

      /* Read ...  */
      regcache_raw_read (regcache, fpnum, mmx_buf);
      /* ... Modify ... (always little endian).  */
      memcpy (mmx_buf, buf, register_size (gdbarch, regnum));
      /* ... Write.  */
      regcache_raw_write (regcache, fpnum, mmx_buf);
    }
  else
    regcache_raw_write (regcache, regnum, buf);
}