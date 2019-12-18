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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 struct regcache* deprecated_find_dummy_frame_regcache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* deprecated_grub_regcache_for_registers (struct regcache*) ; 

char *
deprecated_generic_find_dummy_frame (CORE_ADDR pc, CORE_ADDR fp)
{
  struct regcache *regcache = deprecated_find_dummy_frame_regcache (pc, fp);
  if (regcache == NULL)
    return NULL;
  return deprecated_grub_regcache_for_registers (regcache);
}