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
struct group {int /*<<< orphan*/  gr_gid; } ;
typedef  int /*<<< orphan*/  gid_t ;
struct TYPE_3__ {scalar_t__ valid; char* name; int /*<<< orphan*/  gid; } ;
typedef  TYPE_1__ GIDC ;

/* Variables and functions */
 int /*<<< orphan*/  GID_SZ ; 
 int GNMLEN ; 
 scalar_t__ INVALID ; 
 scalar_t__ VALID ; 
 struct group* getgrnam (char*) ; 
 int /*<<< orphan*/  gropn ; 
 TYPE_1__** grptb ; 
 scalar_t__ grptb_start () ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  setgroupent (int) ; 
 size_t st_hash (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

int
gid_name(char *name, gid_t *gid)
{
	struct group *gr;
	GIDC *ptr;
	int namelen;

	/*
	 * return -1 for mangled names
	 */
	if (((namelen = strlen(name)) == 0) || (name[0] == '\0'))
		return(-1);
	if ((grptb == NULL) && (grptb_start() < 0))
		return(-1);

	/*
	 * look up in hash table, if found and valid return the uid,
	 * if found and invalid, return a -1
	 */
	ptr = grptb[st_hash(name, namelen, GID_SZ)];
	if ((ptr != NULL) && (ptr->valid > 0) && !strcmp(name, ptr->name)) {
		if (ptr->valid == INVALID)
			return(-1);
		*gid = ptr->gid;
		return(0);
	}

	if (!gropn) {
		setgroupent(1);
		++gropn;
	}
	if (ptr == NULL)
		ptr = grptb[st_hash(name, namelen, GID_SZ)] =
		  (GIDC *)malloc(sizeof(GIDC));

	/*
	 * no match, look it up, if no match store it as an invalid entry,
	 * or store the matching gid
	 */
	if (ptr == NULL) {
		if ((gr = getgrnam(name)) == NULL)
			return(-1);
		*gid = gr->gr_gid;
		return(0);
	}

	(void)strncpy(ptr->name, name, GNMLEN - 1);
	ptr->name[GNMLEN-1] = '\0';
	if ((gr = getgrnam(name)) == NULL) {
		ptr->valid = INVALID;
		return(-1);
	}
	ptr->valid = VALID;
	*gid = ptr->gid = gr->gr_gid;
	return(0);
}