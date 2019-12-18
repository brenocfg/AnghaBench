#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  shortname; } ;

/* Variables and functions */
 TYPE_1__ gnu_v2_abi_ops ; 
 int /*<<< orphan*/  init_gnuv2_ops () ; 
 int /*<<< orphan*/  register_cp_abi (TYPE_1__*) ; 
 int /*<<< orphan*/  set_cp_abi_as_auto_default (int /*<<< orphan*/ ) ; 

void
_initialize_gnu_v2_abi (void)
{
  init_gnuv2_ops ();
  register_cp_abi (&gnu_v2_abi_ops);
  set_cp_abi_as_auto_default (gnu_v2_abi_ops.shortname);
}