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
typedef  unsigned long u8 ;
typedef  int /*<<< orphan*/  ide_drive_t ;

/* Variables and functions */
 scalar_t__ ide_get_drivedata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u8 QD_TIMING(ide_drive_t *drive)
{
	return (unsigned long)ide_get_drivedata(drive) & 0x00ff;
}