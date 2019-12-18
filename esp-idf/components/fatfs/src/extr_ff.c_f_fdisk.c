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
typedef  int UINT ;
typedef  int /*<<< orphan*/  FRESULT ;
typedef  int DWORD ;
typedef  int DSTATUS ;
typedef  int BYTE ;

/* Variables and functions */
 int CLUSTER_SIZE ; 
 int /*<<< orphan*/  CTRL_SYNC ; 
 int /*<<< orphan*/  FF_MAX_SS ; 
 int /*<<< orphan*/  FR_DISK_ERR ; 
 int /*<<< orphan*/  FR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  FR_NOT_ENOUGH_CORE ; 
 int /*<<< orphan*/  FR_NOT_READY ; 
 int /*<<< orphan*/  FR_OK ; 
 int /*<<< orphan*/  FR_WRITE_PROTECTED ; 
 int /*<<< orphan*/  GET_SECTOR_COUNT ; 
 int /*<<< orphan*/  LEAVE_MKFS (int /*<<< orphan*/ ) ; 
 int MBR_Table ; 
 scalar_t__ RES_OK ; 
 int STA_NOINIT ; 
 int STA_PROTECT ; 
 int SUPPORTED_FLASH_SIZE ; 
 int /*<<< orphan*/  SZ_PTE ; 
 int disk_initialize (int) ; 
 scalar_t__ disk_ioctl (int,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ disk_write (int,int*,int /*<<< orphan*/ ,int) ; 
 int* ff_memalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mem_set (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_dword (int*,int) ; 
 int /*<<< orphan*/  st_word (int*,int) ; 

FRESULT f_fdisk (
	BYTE pdrv,			/* Physical drive number */
	const DWORD* szt,	/* Pointer to the size table for each partitions */
	void* work			/* Pointer to the working buffer (null: use heap memory) */
)
{
	UINT i, n, sz_cyl, tot_cyl, b_cyl, e_cyl, p_cyl;
	BYTE s_hd, e_hd, *p, *buf = (BYTE*)work;
	DSTATUS stat;
	DWORD sz_disk, sz_part, s_part;
	DWORD cluster_size = CLUSTER_SIZE;
	FRESULT res;


	stat = disk_initialize(pdrv);
	if (stat & STA_NOINIT) return FR_NOT_READY;
	if (stat & STA_PROTECT) return FR_WRITE_PROTECTED;
	if (disk_ioctl(pdrv, GET_SECTOR_COUNT, &sz_disk)) return FR_DISK_ERR;

	buf = (BYTE*)work;
#if FF_USE_LFN == 3
	if (!buf) buf = ff_memalloc(FF_MAX_SS);	/* Use heap memory for working buffer */
#endif
	if (!buf) return FR_NOT_ENOUGH_CORE;

	/* Determine the CHS without any consideration of the drive geometry */
	for (n = 16; n < 256 && sz_disk / n / cluster_size > 1024; n *= 2) {
		;
	}
	if (n == 256) n--;
	if (sz_disk < SUPPORTED_FLASH_SIZE) {
		cluster_size = 1;
		n = sz_disk;
	}
	e_hd = n - 1;
	sz_cyl = cluster_size * n;
	tot_cyl = sz_disk / sz_cyl;

	/* Create partition table */
	mem_set(buf, 0, FF_MAX_SS);
	p = buf + MBR_Table; b_cyl = 0;
	for (i = 0; i < 4; i++, p += SZ_PTE) {
		p_cyl = (szt[i] <= 100U) ? (DWORD)tot_cyl * szt[i] / 100 : szt[i] / sz_cyl;	/* Number of cylinders */
		if (p_cyl == 0) continue;
		s_part = (DWORD)sz_cyl * b_cyl;
		sz_part = (DWORD)sz_cyl * p_cyl;
		if (i == 0) {	/* Exclude first track of cylinder 0 */
			s_hd = 1;
			s_part += cluster_size; sz_part -= cluster_size;
		} else {
			s_hd = 0;
		}
		e_cyl = b_cyl + p_cyl - 1;	/* End cylinder */
		if (e_cyl >= tot_cyl) LEAVE_MKFS(FR_INVALID_PARAMETER);

		/* Set partition table */
		p[1] = s_hd;						/* Start head */
		p[2] = (BYTE)(((b_cyl >> 2) & 0xC0) | 1);	/* Start sector */
		p[3] = (BYTE)b_cyl;					/* Start cylinder */
		p[4] = 0x07;						/* System type (temporary setting) */
		p[5] = e_hd;						/* End head */
		p[6] = (BYTE)(((e_cyl >> 2) & 0xC0) | cluster_size);	/* End sector */
		p[7] = (BYTE)e_cyl;					/* End cylinder */
		st_dword(p + 8, s_part);			/* Start sector in LBA */
		st_dword(p + 12, sz_part);			/* Number of sectors */

		/* Next partition */
		b_cyl += p_cyl;
	}
	st_word(p, 0xAA55);		/* MBR signature (always at offset 510) */

	/* Write it to the MBR */
	res = (disk_write(pdrv, buf, 0, 1) == RES_OK && disk_ioctl(pdrv, CTRL_SYNC, 0) == RES_OK) ? FR_OK : FR_DISK_ERR;
	LEAVE_MKFS(res);
}