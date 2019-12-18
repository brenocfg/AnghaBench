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
typedef  int u32 ;
struct qib_devdata {char* boardname; int majrev; int minrev; int /*<<< orphan*/  revision; int /*<<< orphan*/  boardversion; } ;

/* Variables and functions */
 int /*<<< orphan*/  Arch ; 
 int /*<<< orphan*/  BoardID ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int QIB_CHIP_VERS_MAJ ; 
 int QIB_CHIP_VERS_MIN ; 
 int /*<<< orphan*/  Revision ; 
 int /*<<< orphan*/  Revision_R ; 
 int /*<<< orphan*/  SW ; 
 int SYM_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int strlen (char*) ; 

__attribute__((used)) static void pe_boardname(struct qib_devdata *dd)
{
	char *n;
	u32 boardid, namelen;

	boardid = SYM_FIELD(dd->revision, Revision,
			    BoardID);

	switch (boardid) {
	case 2:
		n = "InfiniPath_QLE7140";
		break;
	default:
		qib_dev_err(dd, "Unknown 6120 board with ID %u\n", boardid);
		n = "Unknown_InfiniPath_6120";
		break;
	}
	namelen = strlen(n) + 1;
	dd->boardname = kmalloc(namelen, GFP_KERNEL);
	if (!dd->boardname)
		qib_dev_err(dd, "Failed allocation for board name: %s\n", n);
	else
		snprintf(dd->boardname, namelen, "%s", n);

	if (dd->majrev != 4 || !dd->minrev || dd->minrev > 2)
		qib_dev_err(dd,
			"Unsupported InfiniPath hardware revision %u.%u!\n",
			dd->majrev, dd->minrev);

	snprintf(dd->boardversion, sizeof(dd->boardversion),
		 "ChipABI %u.%u, %s, InfiniPath%u %u.%u, SW Compat %u\n",
		 QIB_CHIP_VERS_MAJ, QIB_CHIP_VERS_MIN, dd->boardname,
		 (unsigned)SYM_FIELD(dd->revision, Revision_R, Arch),
		 dd->majrev, dd->minrev,
		 (unsigned)SYM_FIELD(dd->revision, Revision_R, SW));

}