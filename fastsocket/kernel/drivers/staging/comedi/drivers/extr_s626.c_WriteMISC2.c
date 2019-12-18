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
typedef  int /*<<< orphan*/  uint16_t ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBIwrite (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LP_MISC1 ; 
 int /*<<< orphan*/  LP_WRMISC2 ; 
 int /*<<< orphan*/  MISC1_WDISABLE ; 
 int /*<<< orphan*/  MISC1_WENABLE ; 

__attribute__((used)) static void WriteMISC2(struct comedi_device *dev, uint16_t NewImage)
{
	DEBIwrite(dev, LP_MISC1, MISC1_WENABLE);	/*  enab writes to */
	/*  MISC2 register. */
	DEBIwrite(dev, LP_WRMISC2, NewImage);	/*  Write new image to MISC2. */
	DEBIwrite(dev, LP_MISC1, MISC1_WDISABLE);	/*  Disable writes to MISC2. */
}