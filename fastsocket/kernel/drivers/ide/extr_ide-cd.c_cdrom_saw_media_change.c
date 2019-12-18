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
struct TYPE_3__ {int /*<<< orphan*/  atapi_flags; int /*<<< orphan*/  dev_flags; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int /*<<< orphan*/  IDE_AFLAG_TOC_VALID ; 
 int /*<<< orphan*/  IDE_DFLAG_MEDIA_CHANGED ; 

__attribute__((used)) static void cdrom_saw_media_change(ide_drive_t *drive)
{
	drive->dev_flags |= IDE_DFLAG_MEDIA_CHANGED;
	drive->atapi_flags &= ~IDE_AFLAG_TOC_VALID;
}