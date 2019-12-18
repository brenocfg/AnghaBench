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
struct ab3100 {int chip_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  AB3000 ; 
 int /*<<< orphan*/  AB3100 ; 
 int /*<<< orphan*/  ABUNKNOWN ; 

u8 ab3100_get_chip_type(struct ab3100 *ab3100)
{
	u8 chip = ABUNKNOWN;

	switch (ab3100->chip_id & 0xf0) {
	case  0xa0:
		chip = AB3000;
		break;
	case  0xc0:
		chip = AB3100;
		break;
	}
	return chip;
}