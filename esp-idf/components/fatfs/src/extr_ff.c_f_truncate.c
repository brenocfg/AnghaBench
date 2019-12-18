#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ objsize; int sclust; } ;
struct TYPE_11__ {int n_fatent; int /*<<< orphan*/  pdrv; } ;
struct TYPE_10__ {int flag; scalar_t__ fptr; int /*<<< orphan*/  sect; int /*<<< orphan*/  buf; TYPE_3__ obj; int /*<<< orphan*/  clust; scalar_t__ err; } ;
typedef  scalar_t__ FRESULT ;
typedef  TYPE_1__ FIL ;
typedef  TYPE_2__ FATFS ;
typedef  int DWORD ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ABORT (TYPE_2__*,scalar_t__) ; 
 int FA_DIRTY ; 
 int FA_MODIFIED ; 
 int FA_WRITE ; 
 scalar_t__ FR_DENIED ; 
 scalar_t__ FR_DISK_ERR ; 
 scalar_t__ FR_INT_ERR ; 
 scalar_t__ FR_OK ; 
 int /*<<< orphan*/  LEAVE_FF (TYPE_2__*,scalar_t__) ; 
 scalar_t__ RES_OK ; 
 scalar_t__ disk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int get_fat (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ remove_chain (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ validate (TYPE_3__*,TYPE_2__**) ; 

FRESULT f_truncate (
	FIL* fp		/* Pointer to the file object */
)
{
	FRESULT res;
	FATFS *fs;
	DWORD ncl;


	res = validate(&fp->obj, &fs);	/* Check validity of the file object */
	if (res != FR_OK || (res = (FRESULT)fp->err) != FR_OK) LEAVE_FF(fs, res);
	if (!(fp->flag & FA_WRITE)) LEAVE_FF(fs, FR_DENIED);	/* Check access mode */

	if (fp->fptr < fp->obj.objsize) {	/* Process when fptr is not on the eof */
		if (fp->fptr == 0) {	/* When set file size to zero, remove entire cluster chain */
			res = remove_chain(&fp->obj, fp->obj.sclust, 0);
			fp->obj.sclust = 0;
		} else {				/* When truncate a part of the file, remove remaining clusters */
			ncl = get_fat(&fp->obj, fp->clust);
			res = FR_OK;
			if (ncl == 0xFFFFFFFF) res = FR_DISK_ERR;
			if (ncl == 1) res = FR_INT_ERR;
			if (res == FR_OK && ncl < fs->n_fatent) {
				res = remove_chain(&fp->obj, ncl, fp->clust);
			}
		}
		fp->obj.objsize = fp->fptr;	/* Set file size to current read/write point */
		fp->flag |= FA_MODIFIED;
#if !FF_FS_TINY
		if (res == FR_OK && (fp->flag & FA_DIRTY)) {
			if (disk_write(fs->pdrv, fp->buf, fp->sect, 1) != RES_OK) {
				res = FR_DISK_ERR;
			} else {
				fp->flag &= (BYTE)~FA_DIRTY;
			}
		}
#endif
		if (res != FR_OK) ABORT(fs, res);
	}

	LEAVE_FF(fs, res);
}