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
struct type {int dummy; } ;
struct regcache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IA64_FR8_REGNUM ; 
 int /*<<< orphan*/  IA64_GR8_REGNUM ; 
 int MAX_REGISTER_SIZE ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_FLT ; 
 int /*<<< orphan*/  builtin_type_ia64_ext ; 
 int /*<<< orphan*/  convert_typed_floating (void const*,struct type*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_cooked_write (struct regcache*,int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  target_store_registers (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ia64_store_return_value (struct type *type, struct regcache *regcache, const void *valbuf)
{
  if (TYPE_CODE (type) == TYPE_CODE_FLT)
    {
      char to[MAX_REGISTER_SIZE];
      convert_typed_floating (valbuf, type, to, builtin_type_ia64_ext);
      regcache_cooked_write (regcache, IA64_FR8_REGNUM, (void *)to);
      target_store_registers (IA64_FR8_REGNUM);
    }
  else
    regcache_cooked_write (regcache, IA64_GR8_REGNUM, valbuf);
}