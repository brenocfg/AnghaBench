#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  topo_hdl_t ;
typedef  int /*<<< orphan*/  tnode_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_7__ {char* libzfs_chassis_id; TYPE_2__* libzfs_fru_list; TYPE_2__** libzfs_fru_hash; } ;
typedef  TYPE_1__ libzfs_handle_t ;
struct TYPE_8__ {struct TYPE_8__* zf_next; struct TYPE_8__* zf_chain; struct TYPE_8__* zf_device; int /*<<< orphan*/ * zf_fru; } ;
typedef  TYPE_2__ libzfs_fru_t ;

/* Variables and functions */
 char* FM_FMRI_AUTHORITY ; 
 char* FM_FMRI_AUTH_CHASSIS ; 
 int TOPO_WALK_NEXT ; 
 scalar_t__ _topo_fmri_nvl2str (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**,int*) ; 
 int /*<<< orphan*/  _topo_hdl_strfree (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ _topo_node_fru (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  _topo_node_name (int /*<<< orphan*/ *) ; 
 scalar_t__ _topo_prop_get_string (int /*<<< orphan*/ *,char*,char*,char**,int*) ; 
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 size_t fru_strhash (TYPE_2__*) ; 
 int /*<<< orphan*/ * libzfs_fru_lookup (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 void* strdup (char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

__attribute__((used)) static int
libzfs_fru_gather(topo_hdl_t *thp, tnode_t *tn, void *arg)
{
	libzfs_handle_t *hdl = arg;
	nvlist_t *fru;
	char *devpath, *frustr;
	int err;
	libzfs_fru_t *frup;
	size_t idx;

	/*
	 * If this is the chassis node, and we don't yet have the system
	 * chassis ID, then fill in this value now.
	 */
	if (hdl->libzfs_chassis_id[0] == '\0' &&
	    strcmp(_topo_node_name(tn), "chassis") == 0) {
		if (_topo_prop_get_string(tn, FM_FMRI_AUTHORITY,
		    FM_FMRI_AUTH_CHASSIS, &devpath, &err) == 0)
			(void) strlcpy(hdl->libzfs_chassis_id, devpath,
			    sizeof (hdl->libzfs_chassis_id));
	}

	/*
	 * Skip non-disk nodes.
	 */
	if (strcmp(_topo_node_name(tn), "disk") != 0)
		return (TOPO_WALK_NEXT);

	/*
	 * Get the devfs path and FRU.
	 */
	if (_topo_prop_get_string(tn, "io", "devfs-path", &devpath, &err) != 0)
		return (TOPO_WALK_NEXT);

	if (libzfs_fru_lookup(hdl, devpath) != NULL) {
		_topo_hdl_strfree(thp, devpath);
		return (TOPO_WALK_NEXT);
	}

	if (_topo_node_fru(tn, &fru, NULL, &err) != 0) {
		_topo_hdl_strfree(thp, devpath);
		return (TOPO_WALK_NEXT);
	}

	/*
	 * Convert the FRU into a string.
	 */
	if (_topo_fmri_nvl2str(thp, fru, &frustr, &err) != 0) {
		nvlist_free(fru);
		_topo_hdl_strfree(thp, devpath);
		return (TOPO_WALK_NEXT);
	}

	nvlist_free(fru);

	/*
	 * Finally, we have a FRU string and device path.  Add it to the hash.
	 */
	if ((frup = calloc(sizeof (libzfs_fru_t), 1)) == NULL) {
		_topo_hdl_strfree(thp, devpath);
		_topo_hdl_strfree(thp, frustr);
		return (TOPO_WALK_NEXT);
	}

	if ((frup->zf_device = strdup(devpath)) == NULL ||
	    (frup->zf_fru = strdup(frustr)) == NULL) {
		free(frup->zf_device);
		free(frup);
		_topo_hdl_strfree(thp, devpath);
		_topo_hdl_strfree(thp, frustr);
		return (TOPO_WALK_NEXT);
	}

	_topo_hdl_strfree(thp, devpath);
	_topo_hdl_strfree(thp, frustr);

	idx = fru_strhash(frup->zf_device);
	frup->zf_chain = hdl->libzfs_fru_hash[idx];
	hdl->libzfs_fru_hash[idx] = frup;
	frup->zf_next = hdl->libzfs_fru_list;
	hdl->libzfs_fru_list = frup;

	return (TOPO_WALK_NEXT);
}