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

/* Variables and functions */
 int /*<<< orphan*/  gnu_v3_abi_ops ; 
 int /*<<< orphan*/  init_gnuv3_ops () ; 
 int /*<<< orphan*/  register_cp_abi (int /*<<< orphan*/ *) ; 

void
_initialize_gnu_v3_abi (void)
{
  init_gnuv3_ops ();

  register_cp_abi (&gnu_v3_abi_ops);
}