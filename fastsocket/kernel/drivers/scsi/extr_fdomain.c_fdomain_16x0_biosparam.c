#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct drive_info   TYPE_1__ ;

/* Type definitions */
struct scsi_device {int dummy; } ;
struct block_device {int /*<<< orphan*/  bd_dev; } ;
typedef  int sector_t ;
struct drive_info {unsigned short cylinders; unsigned char heads; unsigned char sectors; } ;

/* Variables and functions */
 scalar_t__ MAJOR (int /*<<< orphan*/ ) ; 
 int MINOR (int /*<<< orphan*/ ) ; 
 int Quantum ; 
 scalar_t__ SCSI_DISK0_MAJOR ; 
 int bios_major ; 
 scalar_t__ bios_mem ; 
 int bios_minor ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 int /*<<< orphan*/  memcpy_fromio (TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  printk (char*) ; 
 unsigned char* scsi_bios_ptable (struct block_device*) ; 

__attribute__((used)) static int fdomain_16x0_biosparam(struct scsi_device *sdev,
		struct block_device *bdev,
		sector_t capacity, int *info_array)
{
   int              drive;
   int		    size      = capacity;
   unsigned long    offset;
   struct drive_info {
      unsigned short cylinders;
      unsigned char  heads;
      unsigned char  sectors;
   } i;
   
   /* NOTES:
      The RAM area starts at 0x1f00 from the bios_base address.

      For BIOS Version 2.0:
      
      The drive parameter table seems to start at 0x1f30.
      The first byte's purpose is not known.
      Next is the cylinder, head, and sector information.
      The last 4 bytes appear to be the drive's size in sectors.
      The other bytes in the drive parameter table are unknown.
      If anyone figures them out, please send me mail, and I will
      update these notes.

      Tape drives do not get placed in this table.

      There is another table at 0x1fea:
      If the byte is 0x01, then the SCSI ID is not in use.
      If the byte is 0x18 or 0x48, then the SCSI ID is in use,
      although tapes don't seem to be in this table.  I haven't
      seen any other numbers (in a limited sample).

      0x1f2d is a drive count (i.e., not including tapes)

      The table at 0x1fcc are I/O ports addresses for the various
      operations.  I calculate these by hand in this driver code.

      
      
      For the ISA-200S version of BIOS Version 2.0:

      The drive parameter table starts at 0x1f33.

      WARNING: Assume that the table entry is 25 bytes long.  Someone needs
      to check this for the Quantum ISA-200S card.

      
      
      For BIOS Version 3.2:

      The drive parameter table starts at 0x1f70.  Each entry is
      0x0a bytes long.  Heads are one less than we need to report.
    */

   if (MAJOR(bdev->bd_dev) != SCSI_DISK0_MAJOR) {
      printk("scsi: <fdomain> fdomain_16x0_biosparam: too many disks");
      return 0;
   }
   drive = MINOR(bdev->bd_dev) >> 4;

   if (bios_major == 2) {
      switch (Quantum) {
      case 2:			/* ISA_200S */
				/* The value of 25 has never been verified.
				   It should probably be 15. */
	 offset = 0x1f33 + drive * 25;
	 break;
      case 3:			/* ISA_250MG */
	 offset = 0x1f36 + drive * 15;
	 break;
      case 4:			/* ISA_200S (another one) */
	 offset = 0x1f34 + drive * 15;
	 break;
      default:
	 offset = 0x1f31 + drive * 25;
	 break;
      }
      memcpy_fromio( &i, bios_mem + offset, sizeof( struct drive_info ) );
      info_array[0] = i.heads;
      info_array[1] = i.sectors;
      info_array[2] = i.cylinders;
   } else if (bios_major == 3
	      && bios_minor >= 0
	      && bios_minor < 4) { /* 3.0 and 3.2 BIOS */
      memcpy_fromio( &i, bios_mem + 0x1f71 + drive * 10,
		     sizeof( struct drive_info ) );
      info_array[0] = i.heads + 1;
      info_array[1] = i.sectors;
      info_array[2] = i.cylinders;
   } else {			/* 3.4 BIOS (and up?) */
      /* This algorithm was provided by Future Domain (much thanks!). */
      unsigned char *p = scsi_bios_ptable(bdev);

      if (p && p[65] == 0xaa && p[64] == 0x55 /* Partition table valid */
	  && p[4]) {			    /* Partition type */

	 /* The partition table layout is as follows:

	    Start: 0x1b3h
	    Offset: 0 = partition status
		    1 = starting head
		    2 = starting sector and cylinder (word, encoded)
		    4 = partition type
		    5 = ending head
		    6 = ending sector and cylinder (word, encoded)
		    8 = starting absolute sector (double word)
		    c = number of sectors (double word)
	    Signature: 0x1fe = 0x55aa

	    So, this algorithm assumes:
	    1) the first partition table is in use,
	    2) the data in the first entry is correct, and
	    3) partitions never divide cylinders

	    Note that (1) may be FALSE for NetBSD (and other BSD flavors),
	    as well as for Linux.  Note also, that Linux doesn't pay any
	    attention to the fields that are used by this algorithm -- it
	    only uses the absolute sector data.  Recent versions of Linux's
	    fdisk(1) will fill this data in correctly, and forthcoming
	    versions will check for consistency.

	    Checking for a non-zero partition type is not part of the
	    Future Domain algorithm, but it seemed to be a reasonable thing
	    to do, especially in the Linux and BSD worlds. */

	 info_array[0] = p[5] + 1;	    /* heads */
	 info_array[1] = p[6] & 0x3f;	    /* sectors */
      } else {

 	 /* Note that this new method guarantees that there will always be
	    less than 1024 cylinders on a platter.  This is good for drives
	    up to approximately 7.85GB (where 1GB = 1024 * 1024 kB). */

	 if ((unsigned int)size >= 0x7e0000U) {
	    info_array[0] = 0xff; /* heads   = 255 */
	    info_array[1] = 0x3f; /* sectors =  63 */
	 } else if ((unsigned int)size >= 0x200000U) {
	    info_array[0] = 0x80; /* heads   = 128 */
	    info_array[1] = 0x3f; /* sectors =  63 */
	 } else {
	    info_array[0] = 0x40; /* heads   =  64 */
	    info_array[1] = 0x20; /* sectors =  32 */
	 }
      }
				/* For both methods, compute the cylinders */
      info_array[2] = (unsigned int)size / (info_array[0] * info_array[1] );
      kfree(p);
   }
   
   return 0;
}