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
struct sa1111_dev {int dummy; } ;
struct sa1111 {int dummy; } ;

/* Variables and functions */
 unsigned int __sa1111_pll_clock (struct sa1111*) ; 
 struct sa1111* sa1111_chip_driver (struct sa1111_dev*) ; 

unsigned int sa1111_pll_clock(struct sa1111_dev *sadev)
{
	struct sa1111 *sachip = sa1111_chip_driver(sadev);

	return __sa1111_pll_clock(sachip);
}