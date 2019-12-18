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

/* Variables and functions */
 int TARGET_CHAR_BIT ; 
 int TYPE_FIELD_BITPOS (struct type*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_gdbarch ; 
 struct type* gdbarch_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtable_field_virtual_functions ; 
 int /*<<< orphan*/  vtable_type_gdbarch_data ; 

__attribute__((used)) static int
vtable_address_point_offset (void)
{
  struct type *vtable_type = gdbarch_data (current_gdbarch,
					   vtable_type_gdbarch_data);

  return (TYPE_FIELD_BITPOS (vtable_type, vtable_field_virtual_functions)
          / TARGET_CHAR_BIT);
}