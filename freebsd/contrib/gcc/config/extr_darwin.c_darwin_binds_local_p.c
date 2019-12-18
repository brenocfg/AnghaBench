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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 scalar_t__ DARWIN_VTABLE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TARGET_KEXTABI ; 
 int default_binds_local_p_1 (int /*<<< orphan*/ ,int) ; 

bool
darwin_binds_local_p (tree decl)
{
  return default_binds_local_p_1 (decl,
				  TARGET_KEXTABI && DARWIN_VTABLE_P (decl));
}