#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ fs; int /*<<< orphan*/  lockid; } ;
struct TYPE_5__ {TYPE_2__ obj; } ;
typedef  scalar_t__ FRESULT ;
typedef  TYPE_1__ FIL ;
typedef  int /*<<< orphan*/  FATFS ;

/* Variables and functions */
 scalar_t__ FR_OK ; 
 scalar_t__ dec_lock (int /*<<< orphan*/ ) ; 
 scalar_t__ f_sync (TYPE_1__*) ; 
 int /*<<< orphan*/  unlock_fs (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ validate (TYPE_2__*,int /*<<< orphan*/ **) ; 

FRESULT f_close (
	FIL* fp		/* Pointer to the file object to be closed */
)
{
	FRESULT res;
	FATFS *fs;

#if !FF_FS_READONLY
	res = f_sync(fp);					/* Flush cached data */
	if (res == FR_OK)
#endif
	{
		res = validate(&fp->obj, &fs);	/* Lock volume */
		if (res == FR_OK) {
#if FF_FS_LOCK != 0
			res = dec_lock(fp->obj.lockid);		/* Decrement file open counter */
			if (res == FR_OK) fp->obj.fs = 0;	/* Invalidate file object */
#else
			fp->obj.fs = 0;	/* Invalidate file object */
#endif
#if FF_FS_REENTRANT
			unlock_fs(fs, FR_OK);		/* Unlock volume */
#endif
		}
	}
	return res;
}