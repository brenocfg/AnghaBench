#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char* uintmax_t ;
typedef  scalar_t__ time_t ;
struct stat {scalar_t__ st_mtime; char* st_size; int /*<<< orphan*/  st_rdev; int /*<<< orphan*/  st_uid; scalar_t__ st_nlink; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_mode; } ;
struct TYPE_3__ {char* name; scalar_t__ type; char* ln_name; struct stat sb; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ ARCHD ;

/* Variables and functions */
 char* CURFRMTD ; 
 char* CURFRMTM ; 
 int DATELEN ; 
 int /*<<< orphan*/  D_MD_ORDER ; 
 int MAJOR (int /*<<< orphan*/ ) ; 
 int MINOR (int /*<<< orphan*/ ) ; 
 int MODELEN ; 
 char* OLDFRMTD ; 
 char* OLDFRMTM ; 
 scalar_t__ PAX_BLK ; 
 scalar_t__ PAX_CHR ; 
 scalar_t__ PAX_HLK ; 
 scalar_t__ PAX_HRG ; 
 scalar_t__ PAX_SLK ; 
 scalar_t__ SIXMONTHS ; 
 int d_first ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  localtime (scalar_t__*) ; 
 int /*<<< orphan*/  name_gid (int /*<<< orphan*/ ,int) ; 
 char* name_uid (int /*<<< orphan*/ ,int) ; 
 char* nl_langinfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 
 scalar_t__ strftime (char*,int,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strmode (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vflag ; 

void
ls_list(ARCHD *arcn, time_t now, FILE *fp)
{
	struct stat *sbp;
	char f_mode[MODELEN];
	char f_date[DATELEN];
	const char *timefrmt;

	/*
	 * if not verbose, just print the file name
	 */
	if (!vflag) {
		(void)fprintf(fp, "%s\n", arcn->name);
		(void)fflush(fp);
		return;
	}

	if (d_first < 0)
		d_first = (*nl_langinfo(D_MD_ORDER) == 'd');
	/*
	 * user wants long mode
	 */
	sbp = &(arcn->sb);
	strmode(sbp->st_mode, f_mode);

	/*
	 * time format based on age compared to the time pax was started.
	 */
	if ((sbp->st_mtime + SIXMONTHS) <= now)
		timefrmt = d_first ? OLDFRMTD : OLDFRMTM;
	else
		timefrmt = d_first ? CURFRMTD : CURFRMTM;

	/*
	 * print file mode, link count, uid, gid and time
	 */
	if (strftime(f_date,DATELEN,timefrmt,localtime(&(sbp->st_mtime))) == 0)
		f_date[0] = '\0';
	(void)fprintf(fp, "%s%2ju %-12s %-12s ", f_mode,
		(uintmax_t)sbp->st_nlink,
		name_uid(sbp->st_uid, 1), name_gid(sbp->st_gid, 1));

	/*
	 * print device id's for devices, or sizes for other nodes
	 */
	if ((arcn->type == PAX_CHR) || (arcn->type == PAX_BLK))
#		ifdef NET2_STAT
		(void)fprintf(fp, "%4u,%4u ", MAJOR(sbp->st_rdev),
		    MINOR(sbp->st_rdev));
#		else
		(void)fprintf(fp, "%4lu,%4lu ", (unsigned long)MAJOR(sbp->st_rdev),
		    (unsigned long)MINOR(sbp->st_rdev));
#		endif
	else {
#		ifdef NET2_STAT
		(void)fprintf(fp, "%9lu ", sbp->st_size);
#		else
		(void)fprintf(fp, "%9ju ", (uintmax_t)sbp->st_size);
#		endif
	}

	/*
	 * print name and link info for hard and soft links
	 */
	(void)fprintf(fp, "%s %s", f_date, arcn->name);
	if ((arcn->type == PAX_HLK) || (arcn->type == PAX_HRG))
		(void)fprintf(fp, " == %s\n", arcn->ln_name);
	else if (arcn->type == PAX_SLK)
		(void)fprintf(fp, " => %s\n", arcn->ln_name);
	else
		(void)putc('\n', fp);
	(void)fflush(fp);
	return;
}