#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ idle_mode; } ;
typedef  TYPE_1__ MGSLPC_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  BIT3 ; 
 scalar_t__ CCR1 ; 
 scalar_t__ CHA ; 
 scalar_t__ HDLC_TXIDLE_FLAGS ; 
 int /*<<< orphan*/  clear_reg_bits (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_reg_bits (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tx_set_idle(MGSLPC_INFO *info)
{
	/* Note: ESCC2 only supports flags and one idle modes */
	if (info->idle_mode == HDLC_TXIDLE_FLAGS)
		set_reg_bits(info, CHA + CCR1, BIT3);
	else
		clear_reg_bits(info, CHA + CCR1, BIT3);
}