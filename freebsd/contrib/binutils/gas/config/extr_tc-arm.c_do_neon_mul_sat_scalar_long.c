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
 int N_S16 ; 
 int N_S32 ; 
 int /*<<< orphan*/  neon_mac_reg_scalar_long (int,int) ; 

__attribute__((used)) static void
do_neon_mul_sat_scalar_long (void)
{
  neon_mac_reg_scalar_long (N_S16 | N_S32, N_S16 | N_S32);
}