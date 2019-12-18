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
struct regcache {TYPE_1__* descr; } ;
struct gdbarch {int dummy; } ;
struct TYPE_2__ {struct gdbarch* gdbarch; } ;

/* Variables and functions */

struct gdbarch *
get_regcache_arch (const struct regcache *regcache)
{
  return regcache->descr->gdbarch;
}