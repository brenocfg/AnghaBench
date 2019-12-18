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
struct l64781_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  l64781_writereg (struct l64781_state*,int,int) ; 

__attribute__((used)) static void apply_tps (struct l64781_state* state)
{
	l64781_writereg (state, 0x2a, 0x00);
	l64781_writereg (state, 0x2a, 0x01);

	/* This here is a little bit questionable because it enables
	   the automatic update of TPS registers. I think we'd need to
	   handle the IRQ from FE to update some other registers as
	   well, or at least implement some magic to tuning to correct
	   to the TPS received from transmission. */
	l64781_writereg (state, 0x2a, 0x02);
}