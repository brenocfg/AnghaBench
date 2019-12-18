#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pl022 {int /*<<< orphan*/  virtbase; TYPE_2__* cur_msg; int /*<<< orphan*/  cur_transfer; TYPE_1__* cur_chip; } ;
struct TYPE_4__ {int /*<<< orphan*/  status; int /*<<< orphan*/  state; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* cs_control ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int ENABLE_ALL_INTERRUPTS ; 
 int /*<<< orphan*/  SSP_CHIP_SELECT ; 
 int /*<<< orphan*/  SSP_CR1 (int /*<<< orphan*/ ) ; 
 int SSP_CR1_MASK_SSE ; 
 int /*<<< orphan*/  SSP_IMSC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATE_ERROR ; 
 int /*<<< orphan*/  giveback (struct pl022*) ; 
 int readw (int /*<<< orphan*/ ) ; 
 scalar_t__ set_up_next_transfer (struct pl022*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_interrupt_transfer(void *data)
{
	struct pl022 *pl022 = data;

	/* Enable target chip */
	pl022->cur_chip->cs_control(SSP_CHIP_SELECT);
	if (set_up_next_transfer(pl022, pl022->cur_transfer)) {
		/* Error path */
		pl022->cur_msg->state = STATE_ERROR;
		pl022->cur_msg->status = -EIO;
		giveback(pl022);
		return;
	}
	/* Enable SSP, turn on interrupts */
	writew((readw(SSP_CR1(pl022->virtbase)) | SSP_CR1_MASK_SSE),
	       SSP_CR1(pl022->virtbase));
	writew(ENABLE_ALL_INTERRUPTS, SSP_IMSC(pl022->virtbase));
}