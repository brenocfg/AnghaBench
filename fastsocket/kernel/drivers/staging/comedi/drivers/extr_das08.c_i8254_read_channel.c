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
struct i8254_struct {int* logic2phys; int /*<<< orphan*/  iobase; } ;

/* Variables and functions */
 unsigned int i8254_read_channel_low (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned int i8254_read_channel(struct i8254_struct *st, int channel)
{
	int chan = st->logic2phys[channel];

	return i8254_read_channel_low(st->iobase, chan);
}