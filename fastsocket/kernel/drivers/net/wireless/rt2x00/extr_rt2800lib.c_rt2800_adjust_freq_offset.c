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
typedef  int /*<<< orphan*/  u8 ;
struct rt2x00_dev {scalar_t__ freq_offset; } ;

/* Variables and functions */
 scalar_t__ FREQ_OFFSET_BOUND ; 
 int /*<<< orphan*/  RFCSR17_CODE ; 
 int /*<<< orphan*/  rt2800_rfcsr_read (struct rt2x00_dev*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2800_rfcsr_write (struct rt2x00_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void rt2800_adjust_freq_offset(struct rt2x00_dev *rt2x00dev)
{
	u8 rfcsr;

	rt2800_rfcsr_read(rt2x00dev, 17, &rfcsr);
	if (rt2x00dev->freq_offset > FREQ_OFFSET_BOUND)
		rt2x00_set_field8(&rfcsr, RFCSR17_CODE, FREQ_OFFSET_BOUND);
	else
		rt2x00_set_field8(&rfcsr, RFCSR17_CODE, rt2x00dev->freq_offset);
	rt2800_rfcsr_write(rt2x00dev, 17, rfcsr);
}