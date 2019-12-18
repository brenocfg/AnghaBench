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
 int /*<<< orphan*/  ALPHA_V0_REGNUM ; 
 int /*<<< orphan*/  regcache_cooked_read_unsigned (struct regcache*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static CORE_ADDR
alpha_extract_struct_value_address (struct regcache *regcache)
{
  ULONGEST addr;
  regcache_cooked_read_unsigned (regcache, ALPHA_V0_REGNUM, &addr);
  return addr;
}