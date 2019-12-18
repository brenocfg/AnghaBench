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
struct TYPE_3__ {int /*<<< orphan*/  sobj; } ;
typedef  scalar_t__ FRESULT ;
typedef  TYPE_1__ FATFS ;

/* Variables and functions */
 scalar_t__ FR_INVALID_DRIVE ; 
 scalar_t__ FR_NOT_ENABLED ; 
 scalar_t__ FR_TIMEOUT ; 
 int /*<<< orphan*/  ff_rel_grant (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unlock_fs (
	FATFS* fs,		/* Filesystem object */
	FRESULT res		/* Result code to be returned */
)
{
	if (fs && res != FR_NOT_ENABLED && res != FR_INVALID_DRIVE && res != FR_TIMEOUT) {
		ff_rel_grant(fs->sobj);
	}
}