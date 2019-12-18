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
typedef  int /*<<< orphan*/  uid_t ;
struct passwd {int /*<<< orphan*/  pw_uid; } ;
struct TYPE_3__ {scalar_t__ valid; char* name; int /*<<< orphan*/  uid; } ;
typedef  TYPE_1__ UIDC ;

/* Variables and functions */
 scalar_t__ INVALID ; 
 int UNMLEN ; 
 int /*<<< orphan*/  UNM_SZ ; 
 scalar_t__ VALID ; 
 struct passwd* getpwnam (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  pwopn ; 
 int /*<<< orphan*/  setpassent (int) ; 
 size_t st_hash (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 TYPE_1__** usrtb ; 
 scalar_t__ usrtb_start () ; 

int
uid_name(char *name, uid_t *uid)
{
	struct passwd *pw;
	UIDC *ptr;
	int namelen;

	/*
	 * return -1 for mangled names
	 */
	if (((namelen = strlen(name)) == 0) || (name[0] == '\0'))
		return(-1);
	if ((usrtb == NULL) && (usrtb_start() < 0))
		return(-1);

	/*
	 * look up in hash table, if found and valid return the uid,
	 * if found and invalid, return a -1
	 */
	ptr = usrtb[st_hash(name, namelen, UNM_SZ)];
	if ((ptr != NULL) && (ptr->valid > 0) && !strcmp(name, ptr->name)) {
		if (ptr->valid == INVALID)
			return(-1);
		*uid = ptr->uid;
		return(0);
	}

	if (!pwopn) {
		setpassent(1);
		++pwopn;
	}

	if (ptr == NULL)
		ptr = usrtb[st_hash(name, namelen, UNM_SZ)] =
		  (UIDC *)malloc(sizeof(UIDC));

	/*
	 * no match, look it up, if no match store it as an invalid entry,
	 * or store the matching uid
	 */
	if (ptr == NULL) {
		if ((pw = getpwnam(name)) == NULL)
			return(-1);
		*uid = pw->pw_uid;
		return(0);
	}
	(void)strncpy(ptr->name, name, UNMLEN - 1);
	ptr->name[UNMLEN-1] = '\0';
	if ((pw = getpwnam(name)) == NULL) {
		ptr->valid = INVALID;
		return(-1);
	}
	ptr->valid = VALID;
	*uid = ptr->uid = pw->pw_uid;
	return(0);
}