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
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 
 int /*<<< orphan*/ * zfs_get_clones_nvl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
get_clones_string(zfs_handle_t *zhp, char *propbuf, size_t proplen)
{
	nvlist_t *value;
	nvpair_t *pair;

	value = zfs_get_clones_nvl(zhp);
	if (value == NULL)
		return (-1);

	propbuf[0] = '\0';
	for (pair = nvlist_next_nvpair(value, NULL); pair != NULL;
	    pair = nvlist_next_nvpair(value, pair)) {
		if (propbuf[0] != '\0')
			(void) strlcat(propbuf, ",", proplen);
		(void) strlcat(propbuf, nvpair_name(pair), proplen);
	}

	return (0);
}