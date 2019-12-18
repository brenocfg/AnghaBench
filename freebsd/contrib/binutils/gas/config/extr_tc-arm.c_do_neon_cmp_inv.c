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
 int N_F32 ; 
 int N_S16 ; 
 int N_S32 ; 
 int N_S8 ; 
 int /*<<< orphan*/  N_SUF_32 ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  neon_compare (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_neon_cmp_inv (void)
{
  neon_compare (N_SUF_32, N_S8 | N_S16 | N_S32 | N_F32, TRUE);
}