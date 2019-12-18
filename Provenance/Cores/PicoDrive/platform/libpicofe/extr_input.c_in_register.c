#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  name ;
struct TYPE_5__ {int (* clean_binds ) (void*,int*,int*) ;} ;
struct TYPE_4__ {char* name; int probed; int* binds; int key_count; int does_combos; int drv_fd_hnd; char const* const* key_names; void* drv_data; int /*<<< orphan*/  drv_id; } ;

/* Variables and functions */
 TYPE_3__ DRV (int /*<<< orphan*/ ) ; 
 int IN_BINDTYPE_COUNT ; 
 int IN_MAX_DEVS ; 
 int /*<<< orphan*/  free (char*) ; 
 int* in_alloc_binds (int /*<<< orphan*/ ,int) ; 
 int in_dev_count ; 
 TYPE_1__* in_devices ; 
 int /*<<< orphan*/  in_free (TYPE_1__*) ; 
 int /*<<< orphan*/  in_probe_dev_id ; 
 int /*<<< orphan*/  lprintf (char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 int stub1 (void*,int*,int*) ; 

void in_register(const char *nname, int drv_fd_hnd, void *drv_data,
		int key_count, const char * const *key_names, int combos)
{
	int i, ret, dupe_count = 0, *binds;
	char name[256], *name_end, *tmp;

	strncpy(name, nname, sizeof(name));
	name[sizeof(name)-12] = 0;
	name_end = name + strlen(name);

	for (i = 0; i < in_dev_count; i++)
	{
		if (in_devices[i].name == NULL)
			continue;
		if (strcmp(in_devices[i].name, name) == 0)
		{
			if (in_devices[i].probed) {
				dupe_count++;
				sprintf(name_end, " [%d]", dupe_count);
				continue;
			}
			goto update;
		}
	}

	if (i >= IN_MAX_DEVS)
	{
		/* try to find unused device */
		for (i = 0; i < IN_MAX_DEVS; i++)
			if (!in_devices[i].probed) break;
		if (i >= IN_MAX_DEVS) {
			lprintf("input: too many devices, can't add %s\n", name);
			return;
		}
		in_free(&in_devices[i]);
	}

	tmp = strdup(name);
	if (tmp == NULL)
		return;

	binds = in_alloc_binds(in_probe_dev_id, key_count);
	if (binds == NULL) {
		free(tmp);
		return;
	}

	in_devices[i].name = tmp;
	in_devices[i].binds = binds;
	in_devices[i].key_count = key_count;
	if (i + 1 > in_dev_count)
		in_dev_count = i + 1;

	lprintf("input: new device #%d \"%s\"\n", i, name);
update:
	in_devices[i].probed = 1;
	in_devices[i].does_combos = combos;
	in_devices[i].drv_id = in_probe_dev_id;
	in_devices[i].drv_fd_hnd = drv_fd_hnd;
	in_devices[i].key_names = key_names;
	in_devices[i].drv_data = drv_data;

	if (in_devices[i].binds != NULL) {
		ret = DRV(in_probe_dev_id).clean_binds(drv_data, in_devices[i].binds,
			in_devices[i].binds + key_count * IN_BINDTYPE_COUNT);
		if (ret == 0) {
			/* no useable binds */
			free(in_devices[i].binds);
			in_devices[i].binds = NULL;
		}
	}
}