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
typedef  int /*<<< orphan*/  zpool_handle_t ;
typedef  scalar_t__ uint_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  g_zfs ; 
 char* gettext (char*) ; 
 int /*<<< orphan*/  print_status_config (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 char* zpool_vdev_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
print_spares(zpool_handle_t *zhp, nvlist_t **spares, uint_t nspares,
    int namewidth)
{
	uint_t i;
	char *name;

	if (nspares == 0)
		return;

	(void) printf(gettext("\tspares\n"));

	for (i = 0; i < nspares; i++) {
		name = zpool_vdev_name(g_zfs, zhp, spares[i], B_FALSE);
		print_status_config(zhp, name, spares[i],
		    namewidth, 2, B_TRUE);
		free(name);
	}
}