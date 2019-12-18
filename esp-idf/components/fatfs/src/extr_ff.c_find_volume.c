#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
typedef  int UINT ;
struct TYPE_10__ {int fs_type; int* win; int fsize; int n_fats; int csize; int n_fatent; int volbase; int database; int fatbase; int dirbase; int bitbase; int last_clst; int free_clst; int n_rootdir; int fsi_flag; scalar_t__ cdir; int /*<<< orphan*/  dirbuf; int /*<<< orphan*/  lfnbuf; scalar_t__ id; int /*<<< orphan*/  pdrv; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int QWORD ;
typedef  scalar_t__ FRESULT ;
typedef  TYPE_1__ FATFS ;
typedef  int DWORD ;
typedef  int DSTATUS ;
typedef  int BYTE ;

/* Variables and functions */
 int BPB_BytsPerSec ; 
 size_t BPB_BytsPerSecEx ; 
 int BPB_DataOfsEx ; 
 int BPB_FATSz16 ; 
 int BPB_FATSz32 ; 
 int BPB_FSInfo32 ; 
 int BPB_FSVer32 ; 
 int BPB_FSVerEx ; 
 int BPB_FatOfsEx ; 
 int BPB_FatSzEx ; 
 int BPB_NumClusEx ; 
 size_t BPB_NumFATs ; 
 size_t BPB_NumFATsEx ; 
 int BPB_RootClus32 ; 
 int BPB_RootClusEx ; 
 int BPB_RootEntCnt ; 
 int BPB_RsvdSecCnt ; 
 size_t BPB_SecPerClus ; 
 size_t BPB_SecPerClusEx ; 
 int BPB_TotSec16 ; 
 int BPB_TotSec32 ; 
 int BPB_TotSecEx ; 
 int BPB_ZeroedEx ; 
 int BS_55AA ; 
 int /*<<< orphan*/  DirBuf ; 
 scalar_t__ ET_BITMAP ; 
 scalar_t__ FA_READ ; 
 int /*<<< orphan*/  FF_FS_READONLY ; 
 int FF_MAX_SS ; 
 int FF_MIN_SS ; 
 scalar_t__ FR_DISK_ERR ; 
 scalar_t__ FR_INVALID_DRIVE ; 
 scalar_t__ FR_NOT_ENABLED ; 
 scalar_t__ FR_NOT_READY ; 
 scalar_t__ FR_NO_FILESYSTEM ; 
 scalar_t__ FR_OK ; 
 scalar_t__ FR_TIMEOUT ; 
 scalar_t__ FR_WRITE_PROTECTED ; 
 int FSI_Free_Count ; 
 int FSI_LeadSig ; 
 int FSI_Nxt_Free ; 
 int FSI_StrucSig ; 
 int FS_EXFAT ; 
 int FS_FAT12 ; 
 int FS_FAT16 ; 
 int FS_FAT32 ; 
 TYPE_1__** FatFs ; 
 scalar_t__ Fsid ; 
 int /*<<< orphan*/  GET_SECTOR_SIZE ; 
 int /*<<< orphan*/  LD2PD (int) ; 
 int LD2PT (int) ; 
 int /*<<< orphan*/  LfnBuf ; 
 int MAX_EXFAT ; 
 int MAX_FAT12 ; 
 int MAX_FAT16 ; 
 int MAX_FAT32 ; 
 int MBR_Table ; 
 int PTE_StLba ; 
 size_t PTE_System ; 
 scalar_t__ RES_OK ; 
 int SS (TYPE_1__*) ; 
 int STA_NOINIT ; 
 int STA_PROTECT ; 
 int SZDIRE ; 
 int SZ_PTE ; 
 int check_fs (TYPE_1__*,int) ; 
 int /*<<< orphan*/  clear_lock (TYPE_1__*) ; 
 int clst2sect (TYPE_1__*,int) ; 
 int disk_initialize (int /*<<< orphan*/ ) ; 
 scalar_t__ disk_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int disk_status (int /*<<< orphan*/ ) ; 
 int get_ldnumber (int /*<<< orphan*/  const**) ; 
 int ld_dword (int*) ; 
 int ld_qword (int*) ; 
 int ld_word (scalar_t__*) ; 
 int /*<<< orphan*/  lock_fs (TYPE_1__*) ; 
 scalar_t__ move_window (TYPE_1__*,int) ; 

__attribute__((used)) static FRESULT find_volume (	/* FR_OK(0): successful, !=0: an error occurred */
	const TCHAR** path,			/* Pointer to pointer to the path name (drive number) */
	FATFS** rfs,				/* Pointer to pointer to the found filesystem object */
	BYTE mode					/* !=0: Check write protection for write access */
)
{
	BYTE fmt, *pt;
	int vol;
	DSTATUS stat;
	DWORD bsect, fasize, tsect, sysect, nclst, szbfat, br[4];
	WORD nrsv;
	FATFS *fs;
	UINT i;


	/* Get logical drive number */
	*rfs = 0;
	vol = get_ldnumber(path);
	if (vol < 0) return FR_INVALID_DRIVE;

	/* Check if the filesystem object is valid or not */
	fs = FatFs[vol];					/* Get pointer to the filesystem object */
	if (!fs) return FR_NOT_ENABLED;		/* Is the filesystem object available? */
#if FF_FS_REENTRANT
	if (!lock_fs(fs)) return FR_TIMEOUT;	/* Lock the volume */
#endif
	*rfs = fs;							/* Return pointer to the filesystem object */

	mode &= (BYTE)~FA_READ;				/* Desired access mode, write access or not */
	if (fs->fs_type != 0) {				/* If the volume has been mounted */
		stat = disk_status(fs->pdrv);
		if (!(stat & STA_NOINIT)) {		/* and the physical drive is kept initialized */
			if (!FF_FS_READONLY && mode && (stat & STA_PROTECT)) {	/* Check write protection if needed */
				return FR_WRITE_PROTECTED;
			}
			return FR_OK;				/* The filesystem object is valid */
		}
	}

	/* The filesystem object is not valid. */
	/* Following code attempts to mount the volume. (analyze BPB and initialize the filesystem object) */

	fs->fs_type = 0;					/* Clear the filesystem object */
	fs->pdrv = LD2PD(vol);				/* Bind the logical drive and a physical drive */
	stat = disk_initialize(fs->pdrv);	/* Initialize the physical drive */
	if (stat & STA_NOINIT) { 			/* Check if the initialization succeeded */
		return FR_NOT_READY;			/* Failed to initialize due to no medium or hard error */
	}
	if (!FF_FS_READONLY && mode && (stat & STA_PROTECT)) { /* Check disk write protection if needed */
		return FR_WRITE_PROTECTED;
	}
#if FF_MAX_SS != FF_MIN_SS				/* Get sector size (multiple sector size cfg only) */
	if (disk_ioctl(fs->pdrv, GET_SECTOR_SIZE, &SS(fs)) != RES_OK) return FR_DISK_ERR;
	if (SS(fs) > FF_MAX_SS || SS(fs) < FF_MIN_SS || (SS(fs) & (SS(fs) - 1))) return FR_DISK_ERR;
#endif

	/* Find an FAT partition on the drive. Supports only generic partitioning rules, FDISK (MBR) and SFD (w/o partition). */
	bsect = 0;
	fmt = check_fs(fs, bsect);			/* Load sector 0 and check if it is an FAT-VBR as SFD */
	if (fmt == 2 || (fmt < 2 && LD2PT(vol) != 0)) {	/* Not an FAT-VBR or forced partition number */
		for (i = 0; i < 4; i++) {		/* Get partition offset */
			pt = fs->win + (MBR_Table + i * SZ_PTE);
			br[i] = pt[PTE_System] ? ld_dword(pt + PTE_StLba) : 0;
		}
		i = LD2PT(vol);					/* Partition number: 0:auto, 1-4:forced */
		if (i != 0) i--;
		do {							/* Find an FAT volume */
			bsect = br[i];
			fmt = bsect ? check_fs(fs, bsect) : 3;	/* Check the partition */
		} while (LD2PT(vol) == 0 && fmt >= 2 && ++i < 4);
	}
	if (fmt == 4) return FR_DISK_ERR;		/* An error occured in the disk I/O layer */
	if (fmt >= 2) return FR_NO_FILESYSTEM;	/* No FAT volume is found */

	/* An FAT volume is found (bsect). Following code initializes the filesystem object */

#if FF_FS_EXFAT
	if (fmt == 1) {
		QWORD maxlba;
		DWORD so, cv, bcl;

		for (i = BPB_ZeroedEx; i < BPB_ZeroedEx + 53 && fs->win[i] == 0; i++) ;	/* Check zero filler */
		if (i < BPB_ZeroedEx + 53) return FR_NO_FILESYSTEM;

		if (ld_word(fs->win + BPB_FSVerEx) != 0x100) return FR_NO_FILESYSTEM;	/* Check exFAT version (must be version 1.0) */

		if (1 << fs->win[BPB_BytsPerSecEx] != SS(fs)) {	/* (BPB_BytsPerSecEx must be equal to the physical sector size) */
			return FR_NO_FILESYSTEM;
		}

		maxlba = ld_qword(fs->win + BPB_TotSecEx) + bsect;	/* Last LBA + 1 of the volume */
		if (maxlba >= 0x100000000) return FR_NO_FILESYSTEM;	/* (It cannot be handled in 32-bit LBA) */

		fs->fsize = ld_dword(fs->win + BPB_FatSzEx);	/* Number of sectors per FAT */

		fs->n_fats = fs->win[BPB_NumFATsEx];			/* Number of FATs */
		if (fs->n_fats != 1) return FR_NO_FILESYSTEM;	/* (Supports only 1 FAT) */

		fs->csize = 1 << fs->win[BPB_SecPerClusEx];		/* Cluster size */
		if (fs->csize == 0)	return FR_NO_FILESYSTEM;	/* (Must be 1..32768) */

		nclst = ld_dword(fs->win + BPB_NumClusEx);		/* Number of clusters */
		if (nclst > MAX_EXFAT) return FR_NO_FILESYSTEM;	/* (Too many clusters) */
		fs->n_fatent = nclst + 2;

		/* Boundaries and Limits */
		fs->volbase = bsect;
		fs->database = bsect + ld_dword(fs->win + BPB_DataOfsEx);
		fs->fatbase = bsect + ld_dword(fs->win + BPB_FatOfsEx);
		if (maxlba < (QWORD)fs->database + nclst * fs->csize) return FR_NO_FILESYSTEM;	/* (Volume size must not be smaller than the size requiered) */
		fs->dirbase = ld_dword(fs->win + BPB_RootClusEx);

		/* Get bitmap location and check if it is contiguous (implementation assumption) */
		so = i = 0;
		for (;;) {	/* Find the bitmap entry in the root directory (in only first cluster) */
			if (i == 0) {
				if (so >= fs->csize) return FR_NO_FILESYSTEM;	/* Not found? */
				if (move_window(fs, clst2sect(fs, fs->dirbase) + so) != FR_OK) return FR_DISK_ERR;
				so++;
			}
			if (fs->win[i] == ET_BITMAP) break;				/* Is it a bitmap entry? */
			i = (i + SZDIRE) % SS(fs);	/* Next entry */
		}
		bcl = ld_dword(fs->win + i + 20);					/* Bitmap cluster */
		if (bcl < 2 || bcl >= fs->n_fatent) return FR_NO_FILESYSTEM;
		fs->bitbase = fs->database + fs->csize * (bcl - 2);	/* Bitmap sector */
		for (;;) {	/* Check if bitmap is contiguous */
			if (move_window(fs, fs->fatbase + bcl / (SS(fs) / 4)) != FR_OK) return FR_DISK_ERR;
			cv = ld_dword(fs->win + bcl % (SS(fs) / 4) * 4);
			if (cv == 0xFFFFFFFF) break;				/* Last link? */
			if (cv != ++bcl) return FR_NO_FILESYSTEM;	/* Fragmented? */
		}

#if !FF_FS_READONLY
		fs->last_clst = fs->free_clst = 0xFFFFFFFF;		/* Initialize cluster allocation information */
#endif
		fmt = FS_EXFAT;			/* FAT sub-type */
	} else
#endif	/* FF_FS_EXFAT */
	{
		if (ld_word(fs->win + BPB_BytsPerSec) != SS(fs)) return FR_NO_FILESYSTEM;	/* (BPB_BytsPerSec must be equal to the physical sector size) */

		fasize = ld_word(fs->win + BPB_FATSz16);		/* Number of sectors per FAT */
		if (fasize == 0) fasize = ld_dword(fs->win + BPB_FATSz32);
		fs->fsize = fasize;

		fs->n_fats = fs->win[BPB_NumFATs];				/* Number of FATs */
		if (fs->n_fats != 1 && fs->n_fats != 2) return FR_NO_FILESYSTEM;	/* (Must be 1 or 2) */
		fasize *= fs->n_fats;							/* Number of sectors for FAT area */

		fs->csize = fs->win[BPB_SecPerClus];			/* Cluster size */
		if (fs->csize == 0 || (fs->csize & (fs->csize - 1))) return FR_NO_FILESYSTEM;	/* (Must be power of 2) */

		fs->n_rootdir = ld_word(fs->win + BPB_RootEntCnt);	/* Number of root directory entries */
		if (fs->n_rootdir % (SS(fs) / SZDIRE)) return FR_NO_FILESYSTEM;	/* (Must be sector aligned) */

		tsect = ld_word(fs->win + BPB_TotSec16);		/* Number of sectors on the volume */
		if (tsect == 0) tsect = ld_dword(fs->win + BPB_TotSec32);

		nrsv = ld_word(fs->win + BPB_RsvdSecCnt);		/* Number of reserved sectors */
		if (nrsv == 0) return FR_NO_FILESYSTEM;			/* (Must not be 0) */

		/* Determine the FAT sub type */
		sysect = nrsv + fasize + fs->n_rootdir / (SS(fs) / SZDIRE);	/* RSV + FAT + FF_DIR */
		if (tsect < sysect) return FR_NO_FILESYSTEM;	/* (Invalid volume size) */
		nclst = (tsect - sysect) / fs->csize;			/* Number of clusters */
		if (nclst == 0) return FR_NO_FILESYSTEM;		/* (Invalid volume size) */
		fmt = 0;
		if (nclst <= MAX_FAT32) fmt = FS_FAT32;
		if (nclst <= MAX_FAT16) fmt = FS_FAT16;
		if (nclst <= MAX_FAT12) fmt = FS_FAT12;
		if (fmt == 0) return FR_NO_FILESYSTEM;

		/* Boundaries and Limits */
		fs->n_fatent = nclst + 2;						/* Number of FAT entries */
		fs->volbase = bsect;							/* Volume start sector */
		fs->fatbase = bsect + nrsv; 					/* FAT start sector */
		fs->database = bsect + sysect;					/* Data start sector */
		if (fmt == FS_FAT32) {
			if (ld_word(fs->win + BPB_FSVer32) != 0) return FR_NO_FILESYSTEM;	/* (Must be FAT32 revision 0.0) */
			if (fs->n_rootdir != 0) return FR_NO_FILESYSTEM;	/* (BPB_RootEntCnt must be 0) */
			fs->dirbase = ld_dword(fs->win + BPB_RootClus32);	/* Root directory start cluster */
			szbfat = fs->n_fatent * 4;					/* (Needed FAT size) */
		} else {
			if (fs->n_rootdir == 0)	return FR_NO_FILESYSTEM;	/* (BPB_RootEntCnt must not be 0) */
			fs->dirbase = fs->fatbase + fasize;			/* Root directory start sector */
			szbfat = (fmt == FS_FAT16) ?				/* (Needed FAT size) */
				fs->n_fatent * 2 : fs->n_fatent * 3 / 2 + (fs->n_fatent & 1);
		}
		if (fs->fsize < (szbfat + (SS(fs) - 1)) / SS(fs)) return FR_NO_FILESYSTEM;	/* (BPB_FATSz must not be less than the size needed) */

#if !FF_FS_READONLY
		/* Get FSInfo if available */
		fs->last_clst = fs->free_clst = 0xFFFFFFFF;		/* Initialize cluster allocation information */
		fs->fsi_flag = 0x80;
#if (FF_FS_NOFSINFO & 3) != 3
		if (fmt == FS_FAT32				/* Allow to update FSInfo only if BPB_FSInfo32 == 1 */
			&& ld_word(fs->win + BPB_FSInfo32) == 1
			&& move_window(fs, bsect + 1) == FR_OK)
		{
			fs->fsi_flag = 0;
			if (ld_word(fs->win + BS_55AA) == 0xAA55	/* Load FSInfo data if available */
				&& ld_dword(fs->win + FSI_LeadSig) == 0x41615252
				&& ld_dword(fs->win + FSI_StrucSig) == 0x61417272)
			{
#if (FF_FS_NOFSINFO & 1) == 0
				fs->free_clst = ld_dword(fs->win + FSI_Free_Count);
#endif
#if (FF_FS_NOFSINFO & 2) == 0
				fs->last_clst = ld_dword(fs->win + FSI_Nxt_Free);
#endif
			}
		}
#endif	/* (FF_FS_NOFSINFO & 3) != 3 */
#endif	/* !FF_FS_READONLY */
	}

	fs->fs_type = fmt;		/* FAT sub-type */
	fs->id = ++Fsid;		/* Volume mount ID */
#if FF_USE_LFN == 1
	fs->lfnbuf = LfnBuf;	/* Static LFN working buffer */
#if FF_FS_EXFAT
	fs->dirbuf = DirBuf;	/* Static directory block scratchpad buuffer */
#endif
#endif
#if FF_FS_RPATH != 0
	fs->cdir = 0;			/* Initialize current directory */
#endif
#if FF_FS_LOCK != 0			/* Clear file lock semaphores */
	clear_lock(fs);
#endif
	return FR_OK;
}