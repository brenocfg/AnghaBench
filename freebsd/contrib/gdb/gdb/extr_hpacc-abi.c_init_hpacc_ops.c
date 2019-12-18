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
 int /*<<< orphan*/  gnuv2_baseclass_offset ; 
 TYPE_1__ hpacc_abi_ops ; 
 int /*<<< orphan*/  hpacc_is_constructor_name ; 
 int /*<<< orphan*/  hpacc_is_destructor_name ; 
 int /*<<< orphan*/  hpacc_is_operator_name ; 
 int /*<<< orphan*/  hpacc_is_vtable_name ; 
 int /*<<< orphan*/  hpacc_value_rtti_type ; 
 int /*<<< orphan*/  hpacc_virtual_fn_field ; 

__attribute__((used)) static void
init_hpacc_ops (void)
{
  hpacc_abi_ops.shortname = "hpaCC";
  hpacc_abi_ops.longname = "HP aCC ABI";
  hpacc_abi_ops.doc = "HP aCC ABI";
  hpacc_abi_ops.is_destructor_name = hpacc_is_destructor_name;
  hpacc_abi_ops.is_constructor_name = hpacc_is_constructor_name;
  hpacc_abi_ops.is_vtable_name = hpacc_is_vtable_name;
  hpacc_abi_ops.is_operator_name = hpacc_is_operator_name;
  hpacc_abi_ops.virtual_fn_field = hpacc_virtual_fn_field;
  hpacc_abi_ops.rtti_type = hpacc_value_rtti_type;
  /* It seems that this function is specific to GNU G++ < 3.0.
     However, it is called for data members even in the HP
     case (although not for member functions).
     FIXME: Is that correct?  */
  hpacc_abi_ops.baseclass_offset = gnuv2_baseclass_offset;
}