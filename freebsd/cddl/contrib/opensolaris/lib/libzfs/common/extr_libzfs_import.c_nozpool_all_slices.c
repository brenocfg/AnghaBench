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
typedef  int /*<<< orphan*/  avl_tree_t ;

/* Variables and functions */
 int FD_NUMPART ; 
 int MAXNAMELEN ; 
 int NDKMAP ; 
 int /*<<< orphan*/  check_one_slice (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static void
nozpool_all_slices(avl_tree_t *r, const char *sname)
{
#ifdef illumos
	char diskname[MAXNAMELEN];
	char *ptr;
	int i;

	(void) strncpy(diskname, sname, MAXNAMELEN);
	if (((ptr = strrchr(diskname, 's')) == NULL) &&
	    ((ptr = strrchr(diskname, 'p')) == NULL))
		return;
	ptr[0] = 's';
	ptr[1] = '\0';
	for (i = 0; i < NDKMAP; i++)
		check_one_slice(r, diskname, i, 0, 1);
	ptr[0] = 'p';
	for (i = 0; i <= FD_NUMPART; i++)
		check_one_slice(r, diskname, i, 0, 1);
#endif	/* illumos */
}