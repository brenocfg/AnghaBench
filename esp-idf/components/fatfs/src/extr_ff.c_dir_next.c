#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int stat; TYPE_2__* fs; } ;
struct TYPE_10__ {scalar_t__ fs_type; int n_rootdir; int csize; int n_fatent; scalar_t__ win; } ;
struct TYPE_9__ {int dptr; int clust; scalar_t__ dir; int /*<<< orphan*/  sect; TYPE_3__ obj; } ;
typedef  scalar_t__ FRESULT ;
typedef  TYPE_1__ FF_DIR ;
typedef  TYPE_2__ FATFS ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ FF_FS_EXFAT ; 
 scalar_t__ FR_DENIED ; 
 scalar_t__ FR_DISK_ERR ; 
 scalar_t__ FR_INT_ERR ; 
 scalar_t__ FR_NO_FILE ; 
 scalar_t__ FR_OK ; 
 scalar_t__ FS_EXFAT ; 
 scalar_t__ MAX_DIR ; 
 scalar_t__ MAX_DIR_EX ; 
 int SS (TYPE_2__*) ; 
 int SZDIRE ; 
 int /*<<< orphan*/  clst2sect (TYPE_2__*,int) ; 
 int create_chain (TYPE_3__*,int) ; 
 scalar_t__ dir_clear (TYPE_2__*,int) ; 
 int get_fat (TYPE_3__*,int) ; 

__attribute__((used)) static FRESULT dir_next (	/* FR_OK(0):succeeded, FR_NO_FILE:End of table, FR_DENIED:Could not stretch */
	FF_DIR* dp,				/* Pointer to the directory object */
	int stretch				/* 0: Do not stretch table, 1: Stretch table if needed */
)
{
	DWORD ofs, clst;
	FATFS *fs = dp->obj.fs;


	ofs = dp->dptr + SZDIRE;	/* Next entry */
	if (ofs >= (DWORD)((FF_FS_EXFAT && fs->fs_type == FS_EXFAT) ? MAX_DIR_EX : MAX_DIR)) dp->sect = 0;	/* Disable it if the offset reached the max value */
	if (dp->sect == 0) return FR_NO_FILE;	/* Report EOT if it has been disabled */

	if (ofs % SS(fs) == 0) {	/* Sector changed? */
		dp->sect++;				/* Next sector */

		if (dp->clust == 0) {	/* Static table */
			if (ofs / SZDIRE >= fs->n_rootdir) {	/* Report EOT if it reached end of static table */
				dp->sect = 0; return FR_NO_FILE;
			}
		}
		else {					/* Dynamic table */
			if ((ofs / SS(fs) & (fs->csize - 1)) == 0) {	/* Cluster changed? */
				clst = get_fat(&dp->obj, dp->clust);		/* Get next cluster */
				if (clst <= 1) return FR_INT_ERR;			/* Internal error */
				if (clst == 0xFFFFFFFF) return FR_DISK_ERR;	/* Disk error */
				if (clst >= fs->n_fatent) {					/* It reached end of dynamic table */
#if !FF_FS_READONLY
					if (!stretch) {								/* If no stretch, report EOT */
						dp->sect = 0; return FR_NO_FILE;
					}
					clst = create_chain(&dp->obj, dp->clust);	/* Allocate a cluster */
					if (clst == 0) return FR_DENIED;			/* No free cluster */
					if (clst == 1) return FR_INT_ERR;			/* Internal error */
					if (clst == 0xFFFFFFFF) return FR_DISK_ERR;	/* Disk error */
					if (dir_clear(fs, clst) != FR_OK) return FR_DISK_ERR;	/* Clean up the stretched table */
					if (FF_FS_EXFAT) dp->obj.stat |= 4;			/* exFAT: The directory has been stretched */
#else
					if (!stretch) dp->sect = 0;					/* (this line is to suppress compiler warning) */
					dp->sect = 0; return FR_NO_FILE;			/* Report EOT */
#endif
				}
				dp->clust = clst;		/* Initialize data for new cluster */
				dp->sect = clst2sect(fs, clst);
			}
		}
	}
	dp->dptr = ofs;						/* Current entry */
	dp->dir = fs->win + ofs % SS(fs);	/* Pointer to the entry in the win[] */

	return FR_OK;
}