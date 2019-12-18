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
struct TYPE_3__ {struct TYPE_3__* fow; int /*<<< orphan*/  nname; int /*<<< orphan*/  oname; } ;
typedef  TYPE_1__ NAMT ;

/* Variables and functions */
 int /*<<< orphan*/  N_TAB_SZ ; 
 int l_strncpy (char*,int /*<<< orphan*/ ,size_t) ; 
 TYPE_1__** ntab ; 
 size_t st_hash (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

void
sub_name(char *oname, int *onamelen, size_t onamesize)
{
	NAMT *pt;
	u_int indx;

	if (ntab == NULL)
		return;
	/*
	 * look the name up in the hash table
	 */
	indx = st_hash(oname, *onamelen, N_TAB_SZ);
	if ((pt = ntab[indx]) == NULL)
		return;

	while (pt != NULL) {
		/*
		 * walk down the hash chain looking for a match
		 */
		if (strcmp(oname, pt->oname) == 0) {
			/*
			 * found it, replace it with the new name
			 * and return (we know that oname has enough space)
			 */
			*onamelen = l_strncpy(oname, pt->nname, onamesize - 1);
			oname[*onamelen] = '\0';
			return;
		}
		pt = pt->fow;
	}

	/*
	 * no match, just return
	 */
	return;
}