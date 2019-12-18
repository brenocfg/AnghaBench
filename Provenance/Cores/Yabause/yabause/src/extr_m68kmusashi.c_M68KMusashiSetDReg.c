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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ M68K_REG_D0 ; 
 int /*<<< orphan*/  m68k_set_reg (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void M68KMusashiSetDReg(u32 num, u32 val) {
   m68k_set_reg(M68K_REG_D0 + num, val);
}