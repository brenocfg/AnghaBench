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
struct TYPE_10__ {scalar_t__ zpool_start_block; int /*<<< orphan*/  zpool_config; } ;
typedef  TYPE_2__ zpool_handle_t ;
typedef  scalar_t__ zpool_boot_label_t ;
typedef  int uint64_t ;
struct dk_gpt {int efi_lbasize; int efi_last_u_lba; TYPE_1__* efi_parts; } ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_11__ {scalar_t__ libzfs_printerr; } ;
typedef  TYPE_3__ libzfs_handle_t ;
typedef  int /*<<< orphan*/  errbuf ;
typedef  scalar_t__ diskaddr_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_9__ {int p_size; void* p_tag; scalar_t__ p_start; int /*<<< orphan*/  p_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKUP_SLICE ; 
 int EFI_MIN_RESV_SIZE ; 
 int /*<<< orphan*/  EFI_NUMPAR ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  EZFS_LABELFAILED ; 
 int /*<<< orphan*/  EZFS_NOCAP ; 
 int /*<<< orphan*/  EZFS_OPENFAILED ; 
 scalar_t__ MAXOFFSET_T ; 
 int MAXPATHLEN ; 
 scalar_t__ NEW_START_BLOCK ; 
 int O_NDELAY ; 
 int O_RDWR ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 void* V_RESERVED ; 
 void* V_SYSTEM ; 
 void* V_USR ; 
 char* ZFS_RDISK_ROOT ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TREE ; 
 scalar_t__ ZPOOL_CREATE_BOOT_LABEL ; 
 int /*<<< orphan*/  close (int) ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ efi_alloc_and_init (int,int /*<<< orphan*/ ,struct dk_gpt**) ; 
 int /*<<< orphan*/  efi_free (struct dk_gpt*) ; 
 scalar_t__ efi_write (int,struct dk_gpt*) ; 
 scalar_t__ errno ; 
 scalar_t__ find_start_block (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  no_memory (TYPE_3__*) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  verify (int) ; 
 int zfs_error (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  zfs_nicenum (int,char*,int) ; 

int
zpool_label_disk(libzfs_handle_t *hdl, zpool_handle_t *zhp, const char *name,
    zpool_boot_label_t boot_type, uint64_t boot_size, int *slice)
{
#ifdef illumos
	char path[MAXPATHLEN];
	struct dk_gpt *vtoc;
	int fd;
	size_t resv = EFI_MIN_RESV_SIZE;
	uint64_t slice_size;
	diskaddr_t start_block;
	char errbuf[1024];

	/* prepare an error message just in case */
	(void) snprintf(errbuf, sizeof (errbuf),
	    dgettext(TEXT_DOMAIN, "cannot label '%s'"), name);

	if (zhp) {
		nvlist_t *nvroot;

		verify(nvlist_lookup_nvlist(zhp->zpool_config,
		    ZPOOL_CONFIG_VDEV_TREE, &nvroot) == 0);

		if (zhp->zpool_start_block == 0)
			start_block = find_start_block(nvroot);
		else
			start_block = zhp->zpool_start_block;
		zhp->zpool_start_block = start_block;
	} else {
		/* new pool */
		start_block = NEW_START_BLOCK;
	}

	(void) snprintf(path, sizeof (path), "%s/%s%s", ZFS_RDISK_ROOT, name,
	    BACKUP_SLICE);

	if ((fd = open(path, O_RDWR | O_NDELAY)) < 0) {
		/*
		 * This shouldn't happen.  We've long since verified that this
		 * is a valid device.
		 */
		zfs_error_aux(hdl,
		    dgettext(TEXT_DOMAIN, "unable to open device"));
		return (zfs_error(hdl, EZFS_OPENFAILED, errbuf));
	}

	if (efi_alloc_and_init(fd, EFI_NUMPAR, &vtoc) != 0) {
		/*
		 * The only way this can fail is if we run out of memory, or we
		 * were unable to read the disk's capacity
		 */
		if (errno == ENOMEM)
			(void) no_memory(hdl);

		(void) close(fd);
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "unable to read disk capacity"), name);

		return (zfs_error(hdl, EZFS_NOCAP, errbuf));
	}

	/*
	 * Why we use V_USR: V_BACKUP confuses users, and is considered
	 * disposable by some EFI utilities (since EFI doesn't have a backup
	 * slice).  V_UNASSIGNED is supposed to be used only for zero size
	 * partitions, and efi_write() will fail if we use it.  V_ROOT, V_BOOT,
	 * etc. were all pretty specific.  V_USR is as close to reality as we
	 * can get, in the absence of V_OTHER.
	 */
	/* first fix the partition start block */
	if (start_block == MAXOFFSET_T)
		start_block = NEW_START_BLOCK;

	/*
	 * EFI System partition is using slice 0.
	 * ZFS is on slice 1 and slice 8 is reserved.
	 * We assume the GPT partition table without system
	 * partition has zfs p_start == NEW_START_BLOCK.
	 * If start_block != NEW_START_BLOCK, it means we have
	 * system partition. Correct solution would be to query/cache vtoc
	 * from existing vdev member.
	 */
	if (boot_type == ZPOOL_CREATE_BOOT_LABEL) {
		if (boot_size % vtoc->efi_lbasize != 0) {
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "boot partition size must be a multiple of %d"),
			    vtoc->efi_lbasize);
			(void) close(fd);
			efi_free(vtoc);
			return (zfs_error(hdl, EZFS_LABELFAILED, errbuf));
		}
		/*
		 * System partition size checks.
		 * Note the 1MB is quite arbitrary value, since we
		 * are creating dedicated pool, it should be enough
		 * to hold fat + efi bootloader. May need to be
		 * adjusted if the bootloader size will grow.
		 */
		if (boot_size < 1024 * 1024) {
			char buf[64];
			zfs_nicenum(boot_size, buf, sizeof (buf));
			zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
			    "Specified size %s for EFI System partition is too "
			    "small, the minimum size is 1MB."), buf);
			(void) close(fd);
			efi_free(vtoc);
			return (zfs_error(hdl, EZFS_LABELFAILED, errbuf));
		}
		/* 33MB is tested with mkfs -F pcfs */
		if (hdl->libzfs_printerr &&
		    ((vtoc->efi_lbasize == 512 &&
		    boot_size < 33 * 1024 * 1024) ||
		    (vtoc->efi_lbasize == 4096 &&
		    boot_size < 256 * 1024 * 1024)))  {
			char buf[64];
			zfs_nicenum(boot_size, buf, sizeof (buf));
			(void) fprintf(stderr, dgettext(TEXT_DOMAIN,
			    "Warning: EFI System partition size %s is "
			    "not allowing to create FAT32 file\nsystem, which "
			    "may result in unbootable system.\n"), buf);
		}
		/* Adjust zfs partition start by size of system partition. */
		start_block += boot_size / vtoc->efi_lbasize;
	}

	if (start_block == NEW_START_BLOCK) {
		/*
		 * Use default layout.
		 * ZFS is on slice 0 and slice 8 is reserved.
		 */
		slice_size = vtoc->efi_last_u_lba + 1;
		slice_size -= EFI_MIN_RESV_SIZE;
		slice_size -= start_block;
		if (slice != NULL)
			*slice = 0;

		vtoc->efi_parts[0].p_start = start_block;
		vtoc->efi_parts[0].p_size = slice_size;

		vtoc->efi_parts[0].p_tag = V_USR;
		(void) strcpy(vtoc->efi_parts[0].p_name, "zfs");

		vtoc->efi_parts[8].p_start = slice_size + start_block;
		vtoc->efi_parts[8].p_size = resv;
		vtoc->efi_parts[8].p_tag = V_RESERVED;
	} else {
		slice_size = start_block - NEW_START_BLOCK;
		vtoc->efi_parts[0].p_start = NEW_START_BLOCK;
		vtoc->efi_parts[0].p_size = slice_size;
		vtoc->efi_parts[0].p_tag = V_SYSTEM;
		(void) strcpy(vtoc->efi_parts[0].p_name, "loader");
		if (slice != NULL)
			*slice = 1;
		/* prepare slice 1 */
		slice_size = vtoc->efi_last_u_lba + 1 - slice_size;
		slice_size -= resv;
		slice_size -= NEW_START_BLOCK;
		vtoc->efi_parts[1].p_start = start_block;
		vtoc->efi_parts[1].p_size = slice_size;
		vtoc->efi_parts[1].p_tag = V_USR;
		(void) strcpy(vtoc->efi_parts[1].p_name, "zfs");

		vtoc->efi_parts[8].p_start = slice_size + start_block;
		vtoc->efi_parts[8].p_size = resv;
		vtoc->efi_parts[8].p_tag = V_RESERVED;
	}

	if (efi_write(fd, vtoc) != 0) {
		/*
		 * Some block drivers (like pcata) may not support EFI
		 * GPT labels.  Print out a helpful error message dir-
		 * ecting the user to manually label the disk and give
		 * a specific slice.
		 */
		(void) close(fd);
		efi_free(vtoc);

		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "try using fdisk(1M) and then provide a specific slice"));
		return (zfs_error(hdl, EZFS_LABELFAILED, errbuf));
	}

	(void) close(fd);
	efi_free(vtoc);
#endif /* illumos */
	return (0);
}