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
 scalar_t__ m68k_get_reg (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static u32 M68KMusashiGetDReg(u32 num) {
   return m68k_get_reg(NULL, M68K_REG_D0 + num);
}