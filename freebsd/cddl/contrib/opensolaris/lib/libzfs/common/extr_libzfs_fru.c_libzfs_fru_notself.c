#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* libzfs_chassis_id; int /*<<< orphan*/ * libzfs_fru_hash; } ;
typedef  TYPE_1__ libzfs_handle_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  libzfs_fru_refresh (TYPE_1__*) ; 
 size_t strlen (char*) ; 
 scalar_t__ strncmp (char const*,char*,size_t) ; 
 char* strstr (char const*,char*) ; 

boolean_t
libzfs_fru_notself(libzfs_handle_t *hdl, const char *fru)
{
	const char *chassisid;
	size_t len;

	if (hdl->libzfs_fru_hash == NULL)
		libzfs_fru_refresh(hdl);

	if (hdl->libzfs_chassis_id[0] == '\0')
		return (B_FALSE);

	if (strstr(fru, "/chassis=0/") == NULL)
		return (B_FALSE);

	if ((chassisid = strstr(fru, ":chassis-id=")) == NULL)
		return (B_FALSE);

	chassisid += 12;
	len = strlen(hdl->libzfs_chassis_id);
	if (strncmp(chassisid, hdl->libzfs_chassis_id, len) == 0 &&
	    (chassisid[len] == '/' || chassisid[len] == ':'))
		return (B_FALSE);

	return (B_TRUE);
}