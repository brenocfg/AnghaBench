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
struct regcache {scalar_t__ readonly_p; int /*<<< orphan*/ * register_valid_p; } ;

/* Variables and functions */
 int /*<<< orphan*/  regcache_cooked_read (struct regcache*,int,void*) ; 

__attribute__((used)) static int
do_cooked_read (void *src, int regnum, void *buf)
{
  struct regcache *regcache = src;
  if (!regcache->register_valid_p[regnum] && regcache->readonly_p)
    /* Don't even think about fetching a register from a read-only
       cache when the register isn't yet valid.  There isn't a target
       from which the register value can be fetched.  */
    return 0;
  regcache_cooked_read (regcache, regnum, buf);
  return 1;
}