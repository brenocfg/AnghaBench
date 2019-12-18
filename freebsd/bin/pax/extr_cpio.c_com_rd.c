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
struct TYPE_5__ {int st_mode; scalar_t__ st_size; } ;
struct TYPE_6__ {TYPE_1__ sb; scalar_t__ skip; int /*<<< orphan*/  type; int /*<<< orphan*/  name; int /*<<< orphan*/  org_name; int /*<<< orphan*/ * pat; } ;
typedef  TYPE_2__ ARCHD ;

/* Variables and functions */
 int C_IFMT ; 
#define  C_ISBLK 135 
#define  C_ISCHR 134 
#define  C_ISCTG 133 
#define  C_ISDIR 132 
#define  C_ISFIFO 131 
#define  C_ISLNK 130 
#define  C_ISOCK 129 
#define  C_ISREG 128 
 int /*<<< orphan*/  PAX_BLK ; 
 int /*<<< orphan*/  PAX_CHR ; 
 int /*<<< orphan*/  PAX_DIR ; 
 int /*<<< orphan*/  PAX_FIF ; 
 int /*<<< orphan*/  PAX_REG ; 
 int /*<<< orphan*/  PAX_SCK ; 
 int /*<<< orphan*/  PAX_SLK ; 
 scalar_t__ chk_lnk (TYPE_2__*) ; 

__attribute__((used)) static int
com_rd(ARCHD *arcn)
{
	arcn->skip = 0;
	arcn->pat = NULL;
	arcn->org_name = arcn->name;
	switch(arcn->sb.st_mode & C_IFMT) {
	case C_ISFIFO:
		arcn->type = PAX_FIF;
		break;
	case C_ISDIR:
		arcn->type = PAX_DIR;
		break;
	case C_ISBLK:
		arcn->type = PAX_BLK;
		break;
	case C_ISCHR:
		arcn->type = PAX_CHR;
		break;
	case C_ISLNK:
		arcn->type = PAX_SLK;
		break;
	case C_ISOCK:
		arcn->type = PAX_SCK;
		break;
	case C_ISCTG:
	case C_ISREG:
	default:
		/*
		 * we have file data, set up skip (pad is set in the format
		 * specific sections)
		 */
		arcn->sb.st_mode = (arcn->sb.st_mode & 0xfff) | C_ISREG;
		arcn->type = PAX_REG;
		arcn->skip = arcn->sb.st_size;
		break;
	}
	if (chk_lnk(arcn) < 0)
		return(-1);
	return(0);
}