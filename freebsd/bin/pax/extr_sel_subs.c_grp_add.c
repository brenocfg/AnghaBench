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
typedef  size_t u_int ;
struct group {scalar_t__ gr_gid; } ;
typedef  scalar_t__ gid_t ;
struct TYPE_3__ {scalar_t__ gid; struct TYPE_3__* fow; } ;
typedef  TYPE_1__ GRPT ;

/* Variables and functions */
 unsigned int GRP_TB_SZ ; 
 scalar_t__ atoi (char*) ; 
 scalar_t__ calloc (unsigned int,int) ; 
 int /*<<< orphan*/  endgrent () ; 
 struct group* getgrnam (char*) ; 
 TYPE_1__** grptb ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  paxwarn (int,char*,...) ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ *,int) ; 

int
grp_add(char *str)
{
	u_int indx;
	GRPT *pt;
	struct group *gr;
	gid_t gid;

	/*
	 * create the table if it doesn't exist
	 */
	if ((str == NULL) || (*str == '\0'))
		return(-1);
	if ((grptb == NULL) &&
 	    ((grptb = (GRPT **)calloc(GRP_TB_SZ, sizeof(GRPT *))) == NULL)) {
		paxwarn(1, "Unable to allocate memory fo group selection table");
		return(-1);
	}

	/*
	 * figure out user spec
	 */
	if (str[0] != '#') {
		/*
		 * it is a group name, \# escapes # as first char in group name
		 */
		if ((str[0] == '\\') && (str[1] == '#'))
			++str;
		if ((gr = getgrnam(str)) == NULL) {
			paxwarn(1,"Cannot determine gid for group name: %s", str);
			return(-1);
		}
		gid = gr->gr_gid;
	} else
#		ifdef NET2_STAT
		gid = (gid_t)atoi(str+1);
#		else
		gid = (gid_t)strtoul(str+1, NULL, 10);
#		endif
	endgrent();

	/*
	 * hash it and go down the hash chain (if any) looking for it
	 */
	indx = ((unsigned)gid) % GRP_TB_SZ;
	if ((pt = grptb[indx]) != NULL) {
		while (pt != NULL) {
			if (pt->gid == gid)
				return(0);
			pt = pt->fow;
		}
	}

	/*
	 * gid not in the table, add it to the front of the chain
	 */
	if ((pt = (GRPT *)malloc(sizeof(GRPT))) != NULL) {
		pt->gid = gid;
		pt->fow = grptb[indx];
		grptb[indx] = pt;
		return(0);
	}
	paxwarn(1, "Group selection table out of memory");
	return(-1);
}