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
typedef  int /*<<< orphan*/  bfd_byte ;

/* Variables and functions */
 int /*<<< orphan*/  DEPRECATED_EXTRACT_RETURN_VALUE (struct type*,char*,int /*<<< orphan*/ *) ; 
 char* deprecated_grub_regcache_for_registers (struct regcache*) ; 

void
legacy_extract_return_value (struct type *type, struct regcache *regcache,
			     void *valbuf)
{
  char *registers = deprecated_grub_regcache_for_registers (regcache);
  bfd_byte *buf = valbuf;
  DEPRECATED_EXTRACT_RETURN_VALUE (type, registers, buf); /* OK */
}