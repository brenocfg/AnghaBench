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
typedef  int u8 ;
struct ata_scsi_args {int dummy; } ;
typedef  int /*<<< orphan*/  pages ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 

__attribute__((used)) static unsigned int ata_scsiop_inq_00(struct ata_scsi_args *args, u8 *rbuf)
{
	const u8 pages[] = {
		0x00,	/* page 0x00, this page */
		0x80,	/* page 0x80, unit serial no page */
		0x83,	/* page 0x83, device ident page */
		0x89,	/* page 0x89, ata info page */
		0xb0,	/* page 0xb0, block limits page */
		0xb1,	/* page 0xb1, block device characteristics page */
		0xb2,	/* page 0xb2, thin provisioning page */
	};

	rbuf[3] = sizeof(pages);	/* number of supported VPD pages */
	memcpy(rbuf + 4, pages, sizeof(pages));
	return 0;
}