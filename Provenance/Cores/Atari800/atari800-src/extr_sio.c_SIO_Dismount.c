#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ sectors; } ;
typedef  TYPE_1__ vapi_additional_info_t ;
struct TYPE_4__ {scalar_t__ count; } ;
typedef  TYPE_2__ pro_additional_info_t ;

/* Variables and functions */
 scalar_t__ IMAGE_TYPE_PRO ; 
 scalar_t__ IMAGE_TYPE_VAPI ; 
 int /*<<< orphan*/  SIO_NO_DISK ; 
 int /*<<< orphan*/ * SIO_drive_status ; 
 int /*<<< orphan*/ * SIO_filename ; 
 int /*<<< orphan*/  Util_fclose (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__* additional_info ; 
 int /*<<< orphan*/ ** disk ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__* image_type ; 
 int /*<<< orphan*/ * sio_tmpbuf ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

void SIO_Dismount(int diskno)
{
	if (disk[diskno - 1] != NULL) {
		Util_fclose(disk[diskno - 1], sio_tmpbuf[diskno - 1]);
		disk[diskno - 1] = NULL;
		SIO_drive_status[diskno - 1] = SIO_NO_DISK;
		strcpy(SIO_filename[diskno - 1], "Empty");
		if (image_type[diskno - 1] == IMAGE_TYPE_PRO) {
			free(((pro_additional_info_t *)additional_info[diskno-1])->count);
		}
		else if (image_type[diskno - 1] == IMAGE_TYPE_VAPI) {
			free(((vapi_additional_info_t *)additional_info[diskno-1])->sectors);
		}
		free(additional_info[diskno - 1]);
		additional_info[diskno - 1] = 0;
	}
}