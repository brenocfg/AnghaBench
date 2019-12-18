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
typedef  scalar_t__ uid_t ;
typedef  size_t u_int ;
struct passwd {scalar_t__ pw_uid; } ;
struct TYPE_3__ {scalar_t__ uid; struct TYPE_3__* fow; } ;
typedef  TYPE_1__ USRT ;

/* Variables and functions */
 unsigned int USR_TB_SZ ; 
 scalar_t__ atoi (char*) ; 
 scalar_t__ calloc (unsigned int,int) ; 
 int /*<<< orphan*/  endpwent () ; 
 struct passwd* getpwnam (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  paxwarn (int,char*,...) ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ *,int) ; 
 TYPE_1__** usrtb ; 

int
usr_add(char *str)
{
	u_int indx;
	USRT *pt;
	struct passwd *pw;
	uid_t uid;

	/*
	 * create the table if it doesn't exist
	 */
	if ((str == NULL) || (*str == '\0'))
		return(-1);
	if ((usrtb == NULL) &&
 	    ((usrtb = (USRT **)calloc(USR_TB_SZ, sizeof(USRT *))) == NULL)) {
		paxwarn(1, "Unable to allocate memory for user selection table");
		return(-1);
	}

	/*
	 * figure out user spec
	 */
	if (str[0] != '#') {
		/*
		 * it is a user name, \# escapes # as first char in user name
		 */
		if ((str[0] == '\\') && (str[1] == '#'))
			++str;
		if ((pw = getpwnam(str)) == NULL) {
			paxwarn(1, "Unable to find uid for user: %s", str);
			return(-1);
		}
		uid = (uid_t)pw->pw_uid;
	} else
#		ifdef NET2_STAT
		uid = (uid_t)atoi(str+1);
#		else
		uid = (uid_t)strtoul(str+1, NULL, 10);
#		endif
	endpwent();

	/*
	 * hash it and go down the hash chain (if any) looking for it
	 */
	indx = ((unsigned)uid) % USR_TB_SZ;
	if ((pt = usrtb[indx]) != NULL) {
		while (pt != NULL) {
			if (pt->uid == uid)
				return(0);
			pt = pt->fow;
		}
	}

	/*
	 * uid is not yet in the table, add it to the front of the chain
	 */
	if ((pt = (USRT *)malloc(sizeof(USRT))) != NULL) {
		pt->uid = uid;
		pt->fow = usrtb[indx];
		usrtb[indx] = pt;
		return(0);
	}
	paxwarn(1, "User selection table out of memory");
	return(-1);
}