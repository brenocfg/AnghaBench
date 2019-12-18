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
typedef  int u8 ;
struct timeval {int tv_sec; int tv_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,long,...) ; 
 int /*<<< orphan*/  do_gettimeofday (struct timeval*) ; 
 int inb (unsigned long) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  outb (int,unsigned long) ; 
 long read_counter (unsigned long) ; 

__attribute__((used)) static long detect_pll_input_clock(unsigned long dma_base)
{
	struct timeval start_time, end_time;
	long start_count, end_count;
	long pll_input, usec_elapsed;
	u8 scr1;

	start_count = read_counter(dma_base);
	do_gettimeofday(&start_time);

	/* Start the test mode */
	outb(0x01, dma_base + 0x01);
	scr1 = inb(dma_base + 0x03);
	DBG("scr1[%02X]\n", scr1);
	outb(scr1 | 0x40, dma_base + 0x03);

	/* Let the counter run for 10 ms. */
	mdelay(10);

	end_count = read_counter(dma_base);
	do_gettimeofday(&end_time);

	/* Stop the test mode */
	outb(0x01, dma_base + 0x01);
	scr1 = inb(dma_base + 0x03);
	DBG("scr1[%02X]\n", scr1);
	outb(scr1 & ~0x40, dma_base + 0x03);

	/*
	 * Calculate the input clock in Hz
	 * (the clock counter is 30 bit wide and counts down)
	 */
	usec_elapsed = (end_time.tv_sec - start_time.tv_sec) * 1000000 +
		(end_time.tv_usec - start_time.tv_usec);
	pll_input = ((start_count - end_count) & 0x3fffffff) / 10 *
		(10000000 / usec_elapsed);

	DBG("start[%ld] end[%ld]\n", start_count, end_count);

	return pll_input;
}