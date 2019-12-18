#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__** libzfs_fru_hash; } ;
typedef  TYPE_1__ libzfs_handle_t ;
struct TYPE_6__ {char const* zf_fru; int /*<<< orphan*/  zf_device; struct TYPE_6__* zf_chain; } ;
typedef  TYPE_2__ libzfs_fru_t ;

/* Variables and functions */
 size_t fru_strhash (char const*) ; 
 int /*<<< orphan*/  libzfs_fru_refresh (TYPE_1__*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

const char *
libzfs_fru_lookup(libzfs_handle_t *hdl, const char *devpath)
{
	size_t idx = fru_strhash(devpath);
	libzfs_fru_t *frup;

	if (hdl->libzfs_fru_hash == NULL)
		libzfs_fru_refresh(hdl);

	if (hdl->libzfs_fru_hash == NULL)
		return (NULL);

	for (frup = hdl->libzfs_fru_hash[idx]; frup != NULL;
	    frup = frup->zf_chain) {
		if (strcmp(devpath, frup->zf_device) == 0)
			return (frup->zf_fru);
	}

	return (NULL);
}