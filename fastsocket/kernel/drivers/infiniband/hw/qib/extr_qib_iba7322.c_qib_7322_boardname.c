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
struct qib_devdata {int board_atten; char* boardname; int majrev; int minrev; int /*<<< orphan*/  unit; int /*<<< orphan*/  pcidev; int /*<<< orphan*/  revision; int /*<<< orphan*/  boardversion; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  Arch ; 
#define  BOARD_QME7342 129 
#define  BOARD_QMH7342 128 
 int /*<<< orphan*/  BoardID ; 
 unsigned int DUAL_PORT_CAP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int PORT_SPD_CAP ; 
 unsigned int PORT_SPD_CAP_SHIFT ; 
 int QIB_CHIP_VERS_MAJ ; 
 int QIB_CHIP_VERS_MIN ; 
 int /*<<< orphan*/  QIB_HAS_QSFP ; 
 int /*<<< orphan*/  Revision ; 
 int /*<<< orphan*/  Revision_R ; 
 int /*<<< orphan*/  SW ; 
 int SYM_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_dev_err (struct qib_devdata*,char*,...) ; 
 int /*<<< orphan*/  qib_devinfo (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ qib_singleport ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int strlen (char*) ; 

__attribute__((used)) static unsigned qib_7322_boardname(struct qib_devdata *dd)
{
	/* Will need enumeration of board-types here */
	char *n;
	u32 boardid, namelen;
	unsigned features = DUAL_PORT_CAP;

	boardid = SYM_FIELD(dd->revision, Revision, BoardID);

	switch (boardid) {
	case 0:
		n = "InfiniPath_QLE7342_Emulation";
		break;
	case 1:
		n = "InfiniPath_QLE7340";
		dd->flags |= QIB_HAS_QSFP;
		features = PORT_SPD_CAP;
		break;
	case 2:
		n = "InfiniPath_QLE7342";
		dd->flags |= QIB_HAS_QSFP;
		break;
	case 3:
		n = "InfiniPath_QMI7342";
		break;
	case 4:
		n = "InfiniPath_Unsupported7342";
		qib_dev_err(dd, "Unsupported version of QMH7342\n");
		features = 0;
		break;
	case BOARD_QMH7342:
		n = "InfiniPath_QMH7342";
		features = 0x24;
		break;
	case BOARD_QME7342:
		n = "InfiniPath_QME7342";
		break;
	case 8:
		n = "InfiniPath_QME7362";
		dd->flags |= QIB_HAS_QSFP;
		break;
	case 15:
		n = "InfiniPath_QLE7342_TEST";
		dd->flags |= QIB_HAS_QSFP;
		break;
	default:
		n = "InfiniPath_QLE73xy_UNKNOWN";
		qib_dev_err(dd, "Unknown 7322 board type %u\n", boardid);
		break;
	}
	dd->board_atten = 1; /* index into txdds_Xdr */

	namelen = strlen(n) + 1;
	dd->boardname = kmalloc(namelen, GFP_KERNEL);
	if (!dd->boardname)
		qib_dev_err(dd, "Failed allocation for board name: %s\n", n);
	else
		snprintf(dd->boardname, namelen, "%s", n);

	snprintf(dd->boardversion, sizeof(dd->boardversion),
		 "ChipABI %u.%u, %s, InfiniPath%u %u.%u, SW Compat %u\n",
		 QIB_CHIP_VERS_MAJ, QIB_CHIP_VERS_MIN, dd->boardname,
		 (unsigned)SYM_FIELD(dd->revision, Revision_R, Arch),
		 dd->majrev, dd->minrev,
		 (unsigned)SYM_FIELD(dd->revision, Revision_R, SW));

	if (qib_singleport && (features >> PORT_SPD_CAP_SHIFT) & PORT_SPD_CAP) {
		qib_devinfo(dd->pcidev,
			"IB%u: Forced to single port mode by module parameter\n",
			dd->unit);
		features &= PORT_SPD_CAP;
	}

	return features;
}