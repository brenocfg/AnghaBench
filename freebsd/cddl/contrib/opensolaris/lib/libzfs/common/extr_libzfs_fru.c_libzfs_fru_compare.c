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
struct TYPE_4__ {int /*<<< orphan*/  libzfs_topo_hdl; int /*<<< orphan*/ * libzfs_fru_hash; } ;
typedef  TYPE_1__ libzfs_handle_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int _topo_fmri_strcmp_noauth (int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  libzfs_fru_refresh (TYPE_1__*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 

boolean_t
libzfs_fru_compare(libzfs_handle_t *hdl, const char *a, const char *b)
{
	if (hdl->libzfs_fru_hash == NULL)
		libzfs_fru_refresh(hdl);

	if (hdl->libzfs_fru_hash == NULL)
		return (strcmp(a, b) == 0);

	return (_topo_fmri_strcmp_noauth(hdl->libzfs_topo_hdl, a, b));
}