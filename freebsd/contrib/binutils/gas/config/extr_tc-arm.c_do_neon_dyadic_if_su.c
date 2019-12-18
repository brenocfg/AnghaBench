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
 int /*<<< orphan*/  NT_unsigned ; 
 int /*<<< orphan*/  N_SUF_32 ; 
 int /*<<< orphan*/  neon_dyadic_misc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_neon_dyadic_if_su (void)
{
  neon_dyadic_misc (NT_unsigned, N_SUF_32, 0);
}