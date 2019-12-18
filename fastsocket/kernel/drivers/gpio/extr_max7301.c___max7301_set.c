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
struct max7301 {int out_level; int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 int max7301_write (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int __max7301_set(struct max7301 *ts, unsigned offset, int value)
{
	if (value) {
		ts->out_level |= 1 << offset;
		return max7301_write(ts->spi, 0x20 + offset, 0x01);
	} else {
		ts->out_level &= ~(1 << offset);
		return max7301_write(ts->spi, 0x20 + offset, 0x00);
	}
}