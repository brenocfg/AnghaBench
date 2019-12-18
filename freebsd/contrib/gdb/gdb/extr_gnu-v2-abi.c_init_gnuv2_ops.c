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
struct TYPE_2__ {char* shortname; char* longname; char* doc; int /*<<< orphan*/  baseclass_offset; int /*<<< orphan*/  rtti_type; int /*<<< orphan*/  virtual_fn_field; int /*<<< orphan*/  is_operator_name; int /*<<< orphan*/  is_vtable_name; int /*<<< orphan*/  is_constructor_name; int /*<<< orphan*/  is_destructor_name; } ;

/* Variables and functions */
 TYPE_1__ gnu_v2_abi_ops ; 
 int /*<<< orphan*/  gnuv2_baseclass_offset ; 
 int /*<<< orphan*/  gnuv2_is_constructor_name ; 
 int /*<<< orphan*/  gnuv2_is_destructor_name ; 
 int /*<<< orphan*/  gnuv2_is_operator_name ; 
 int /*<<< orphan*/  gnuv2_is_vtable_name ; 
 int /*<<< orphan*/  gnuv2_value_rtti_type ; 
 int /*<<< orphan*/  gnuv2_virtual_fn_field ; 

__attribute__((used)) static void
init_gnuv2_ops (void)
{
  gnu_v2_abi_ops.shortname = "gnu-v2";
  gnu_v2_abi_ops.longname = "GNU G++ Version 2 ABI";
  gnu_v2_abi_ops.doc = "G++ Version 2 ABI";
  gnu_v2_abi_ops.is_destructor_name = gnuv2_is_destructor_name;
  gnu_v2_abi_ops.is_constructor_name = gnuv2_is_constructor_name;
  gnu_v2_abi_ops.is_vtable_name = gnuv2_is_vtable_name;
  gnu_v2_abi_ops.is_operator_name = gnuv2_is_operator_name;
  gnu_v2_abi_ops.virtual_fn_field = gnuv2_virtual_fn_field;
  gnu_v2_abi_ops.rtti_type = gnuv2_value_rtti_type;
  gnu_v2_abi_ops.baseclass_offset = gnuv2_baseclass_offset;
}