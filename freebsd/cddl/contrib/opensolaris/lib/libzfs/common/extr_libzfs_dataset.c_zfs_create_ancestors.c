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
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  errbuf ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  EZFS_INVALIDNAME ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 scalar_t__ check_parents (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int create_parents (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ dataset_nestcheck (char const*) ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 char* strdup (char const*) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,char*) ; 

int
zfs_create_ancestors(libzfs_handle_t *hdl, const char *path)
{
	int prefix;
	char *path_copy;
	char errbuf[1024];
	int rc = 0;

	(void) snprintf(errbuf, sizeof (errbuf), dgettext(TEXT_DOMAIN,
	    "cannot create '%s'"), path);

	/*
	 * Check that we are not passing the nesting limit
	 * before we start creating any ancestors.
	 */
	if (dataset_nestcheck(path) != 0) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN,
		    "maximum name nesting depth exceeded"));
		return (zfs_error(hdl, EZFS_INVALIDNAME, errbuf));
	}

	if (check_parents(hdl, path, NULL, B_TRUE, &prefix) != 0)
		return (-1);

	if ((path_copy = strdup(path)) != NULL) {
		rc = create_parents(hdl, path_copy, prefix);
		free(path_copy);
	}
	if (path_copy == NULL || rc != 0)
		return (-1);

	return (0);
}