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
typedef  int /*<<< orphan*/  uint16_t ;
struct enc_private {scalar_t__ MyLatchLsw; } ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBIwrite (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG (char*) ; 

__attribute__((used)) static void Preload(struct comedi_device *dev, struct enc_private *k,
		    uint32_t value)
{
	DEBUG("Preload: preload enter\n");
	DEBIwrite(dev, (uint16_t) (k->MyLatchLsw), (uint16_t) value);	/*  Write value to preload register. */
	DEBUG("Preload: preload step 1\n");
	DEBIwrite(dev, (uint16_t) (k->MyLatchLsw + 2),
		  (uint16_t) (value >> 16));
}