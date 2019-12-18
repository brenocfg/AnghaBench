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
typedef  int uint32_t ;
struct enc_private {scalar_t__ MyLatchLsw; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ DEBIread (struct comedi_device*,scalar_t__) ; 

__attribute__((used)) static uint32_t ReadLatch(struct comedi_device *dev, struct enc_private *k)
{
	register uint32_t value;
	/* DEBUG FIXME DEBUG("ReadLatch: Read Latch enter\n"); */

	/*  Latch counts and fetch LSW of latched counts value. */
	value = (uint32_t) DEBIread(dev, k->MyLatchLsw);

	/*  Fetch MSW of latched counts and combine with LSW. */
	value |= ((uint32_t) DEBIread(dev, k->MyLatchLsw + 2) << 16);

	/*  DEBUG FIXME DEBUG("ReadLatch: Read Latch exit\n"); */

	/*  Return latched counts. */
	return value;
}