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
 int /*<<< orphan*/  NT_untyped ; 
 int /*<<< orphan*/  N_IF_32 ; 
 int /*<<< orphan*/  neon_dyadic_misc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_neon_dyadic_if_i_d (void)
{
  /* The "untyped" case can't happen. Do this to stop the "U" bit being
     affected if we specify unsigned args.  */
  neon_dyadic_misc (NT_untyped, N_IF_32, 0);
}