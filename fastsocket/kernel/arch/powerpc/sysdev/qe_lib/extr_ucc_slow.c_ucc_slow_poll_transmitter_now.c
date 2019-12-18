#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ucc_slow_private {TYPE_1__* us_regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  utodr; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCC_SLOW_TOD ; 
 int /*<<< orphan*/  out_be16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ucc_slow_poll_transmitter_now(struct ucc_slow_private * uccs)
{
	out_be16(&uccs->us_regs->utodr, UCC_SLOW_TOD);
}