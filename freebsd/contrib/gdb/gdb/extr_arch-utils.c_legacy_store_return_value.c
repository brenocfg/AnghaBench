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
 int /*<<< orphan*/  DEPRECATED_STORE_RETURN_VALUE (struct type*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TYPE_LENGTH (struct type*) ; 
 int /*<<< orphan*/ * alloca (int /*<<< orphan*/ ) ; 
 struct regcache* current_regcache ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ ) ; 

void
legacy_store_return_value (struct type *type, struct regcache *regcache,
			   const void *buf)
{
  bfd_byte *b = alloca (TYPE_LENGTH (type));
  gdb_assert (regcache == current_regcache);
  memcpy (b, buf, TYPE_LENGTH (type));
  DEPRECATED_STORE_RETURN_VALUE (type, b);
}