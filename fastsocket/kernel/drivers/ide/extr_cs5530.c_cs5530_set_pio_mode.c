#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct TYPE_3__ {int dn; int /*<<< orphan*/  hwif; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 unsigned long CS5530_BASEREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** cs5530_pio_timings ; 
 int inl (unsigned long) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void cs5530_set_pio_mode(ide_drive_t *drive, const u8 pio)
{
	unsigned long basereg = CS5530_BASEREG(drive->hwif);
	unsigned int format = (inl(basereg + 4) >> 31) & 1;

	outl(cs5530_pio_timings[format][pio], basereg + ((drive->dn & 1)<<3));
}