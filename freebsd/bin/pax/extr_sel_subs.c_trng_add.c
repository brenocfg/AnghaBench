#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flgs; scalar_t__ low_time; scalar_t__ high_time; struct TYPE_5__* fow; } ;
typedef  TYPE_1__ TIME_RNG ;

/* Variables and functions */
 int CMPCTME ; 
 int CMPMTME ; 
 int HASHIGH ; 
 int HASLOW ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  paxwarn (int,char*,...) ; 
 scalar_t__ str_sec (char*,scalar_t__*) ; 
 char* strrchr (char*,char) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 TYPE_1__* trhead ; 
 TYPE_1__* trtail ; 

int
trng_add(char *str)
{
	TIME_RNG *pt;
	char *up_pt = NULL;
	char *stpt;
	char *flgpt;
	int dot = 0;

	/*
	 * throw out the badly formed time ranges
	 */
	if ((str == NULL) || (*str == '\0')) {
		paxwarn(1, "Empty time range string");
		return(-1);
	}

	/*
	 * locate optional flags suffix /{cm}.
	 */
	if ((flgpt = strrchr(str, '/')) != NULL)
		*flgpt++ = '\0';

	for (stpt = str; *stpt != '\0'; ++stpt) {
		if ((*stpt >= '0') && (*stpt <= '9'))
			continue;
		if ((*stpt == ',') && (up_pt == NULL)) {
			*stpt = '\0';
			up_pt = stpt + 1;
			dot = 0;
			continue;
		}

		/*
		 * allow only one dot per range (secs)
		 */
		if ((*stpt == '.') && (!dot)) {
			++dot;
			continue;
		}
		paxwarn(1, "Improperly specified time range: %s", str);
		goto out;
	}

	/*
	 * allocate space for the time range and store the limits
	 */
	if ((pt = (TIME_RNG *)malloc(sizeof(TIME_RNG))) == NULL) {
		paxwarn(1, "Unable to allocate memory for time range");
		return(-1);
	}

	/*
	 * by default we only will check file mtime, but the user can specify
	 * mtime, ctime (inode change time) or both.
	 */
	if ((flgpt == NULL) || (*flgpt == '\0'))
		pt->flgs = CMPMTME;
	else {
		pt->flgs = 0;
		while (*flgpt != '\0') {
			switch(*flgpt) {
			case 'M':
			case 'm':
				pt->flgs |= CMPMTME;
				break;
			case 'C':
			case 'c':
				pt->flgs |= CMPCTME;
				break;
			default:
				paxwarn(1, "Bad option %c with time range %s",
				    *flgpt, str);
				free(pt);
				goto out;
			}
			++flgpt;
		}
	}

	/*
	 * start off with the current time
	 */
	pt->low_time = pt->high_time = time(NULL);
	if (*str != '\0') {
		/*
		 * add lower limit
		 */
		if (str_sec(str, &(pt->low_time)) < 0) {
			paxwarn(1, "Illegal lower time range %s", str);
			free(pt);
			goto out;
		}
		pt->flgs |= HASLOW;
	}

	if ((up_pt != NULL) && (*up_pt != '\0')) {
		/*
		 * add upper limit
		 */
		if (str_sec(up_pt, &(pt->high_time)) < 0) {
			paxwarn(1, "Illegal upper time range %s", up_pt);
			free(pt);
			goto out;
		}
		pt->flgs |= HASHIGH;

		/*
		 * check that the upper and lower do not overlap
		 */
		if (pt->flgs & HASLOW) {
			if (pt->low_time > pt->high_time) {
				paxwarn(1, "Upper %s and lower %s time overlap",
					up_pt, str);
				free(pt);
				return(-1);
			}
		}
	}

	pt->fow = NULL;
	if (trhead == NULL) {
		trtail = trhead = pt;
		return(0);
	}
	trtail->fow = pt;
	trtail = pt;
	return(0);

    out:
	paxwarn(1, "Time range format is: [yy[mm[dd[hh]]]]mm[.ss][/[c][m]]");
	return(-1);
}