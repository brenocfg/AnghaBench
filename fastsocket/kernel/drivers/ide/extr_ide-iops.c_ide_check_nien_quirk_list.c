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
struct TYPE_3__ {int /*<<< orphan*/  dev_flags; int /*<<< orphan*/ * id; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 size_t ATA_ID_PROD ; 
 int /*<<< orphan*/  IDE_DFLAG_NIEN_QUIRK ; 
 char** nien_quirk_list ; 
 int /*<<< orphan*/ * strstr (char const*,char const*) ; 

void ide_check_nien_quirk_list(ide_drive_t *drive)
{
	const char **list, *m = (char *)&drive->id[ATA_ID_PROD];

	for (list = nien_quirk_list; *list != NULL; list++)
		if (strstr(m, *list) != NULL) {
			drive->dev_flags |= IDE_DFLAG_NIEN_QUIRK;
			return;
		}
}