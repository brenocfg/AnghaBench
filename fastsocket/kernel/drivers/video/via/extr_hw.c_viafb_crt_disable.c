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
 scalar_t__ BIT4 ; 
 scalar_t__ BIT5 ; 
 int /*<<< orphan*/  CR36 ; 
 int /*<<< orphan*/  VIACR ; 
 int /*<<< orphan*/  viafb_write_reg_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

void viafb_crt_disable(void)
{
	viafb_write_reg_mask(CR36, VIACR, BIT5 + BIT4, BIT5 + BIT4);
}