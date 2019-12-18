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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_nicenum (int /*<<< orphan*/ ,char*,int) ; 
 int zfs_prop_get_written_int (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 

int
zfs_prop_get_written(zfs_handle_t *zhp, const char *propname,
    char *propbuf, int proplen, boolean_t literal)
{
	int err;
	uint64_t propvalue;

	err = zfs_prop_get_written_int(zhp, propname, &propvalue);

	if (err)
		return (err);

	if (literal) {
		(void) snprintf(propbuf, proplen, "%llu", propvalue);
	} else {
		zfs_nicenum(propvalue, propbuf, proplen);
	}
	return (0);
}