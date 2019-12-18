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
struct TYPE_2__ {char* shortname; char* longname; char* doc; int /*<<< orphan*/  baseclass_offset; int /*<<< orphan*/  virtual_fn_field; int /*<<< orphan*/  rtti_type; int /*<<< orphan*/  is_operator_name; int /*<<< orphan*/  is_vtable_name; int /*<<< orphan*/  is_constructor_name; int /*<<< orphan*/  is_destructor_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  build_gdb_vtable_type ; 
 TYPE_1__ gnu_v3_abi_ops ; 
 int /*<<< orphan*/  gnuv3_baseclass_offset ; 
 int /*<<< orphan*/  gnuv3_is_operator_name ; 
 int /*<<< orphan*/  gnuv3_is_vtable_name ; 
 int /*<<< orphan*/  gnuv3_rtti_type ; 
 int /*<<< orphan*/  gnuv3_virtual_fn_field ; 
 int /*<<< orphan*/  is_gnu_v3_mangled_ctor ; 
 int /*<<< orphan*/  is_gnu_v3_mangled_dtor ; 
 int /*<<< orphan*/  register_gdbarch_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtable_type_gdbarch_data ; 

__attribute__((used)) static void
init_gnuv3_ops (void)
{
  vtable_type_gdbarch_data = register_gdbarch_data (build_gdb_vtable_type);

  gnu_v3_abi_ops.shortname = "gnu-v3";
  gnu_v3_abi_ops.longname = "GNU G++ Version 3 ABI";
  gnu_v3_abi_ops.doc = "G++ Version 3 ABI";
  gnu_v3_abi_ops.is_destructor_name = is_gnu_v3_mangled_dtor;
  gnu_v3_abi_ops.is_constructor_name = is_gnu_v3_mangled_ctor;
  gnu_v3_abi_ops.is_vtable_name = gnuv3_is_vtable_name;
  gnu_v3_abi_ops.is_operator_name = gnuv3_is_operator_name;
  gnu_v3_abi_ops.rtti_type = gnuv3_rtti_type;
  gnu_v3_abi_ops.virtual_fn_field = gnuv3_virtual_fn_field;
  gnu_v3_abi_ops.baseclass_offset = gnuv3_baseclass_offset;
}