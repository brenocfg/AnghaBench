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
typedef  int /*<<< orphan*/ * posix_spawnattr_t ;
typedef  int /*<<< orphan*/  _posix_spawnattr_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  posix_spawn_destroycoalition_info_np (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  posix_spawn_destroypersona_info_np (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  posix_spawn_destroyportactions_np (int /*<<< orphan*/ **) ; 

int
posix_spawnattr_destroy(posix_spawnattr_t *attr)
{
	_posix_spawnattr_t psattr;

	if (attr == NULL || *attr == NULL)
		return EINVAL;

	psattr = *(_posix_spawnattr_t *)attr;
	posix_spawn_destroyportactions_np(attr);
	posix_spawn_destroycoalition_info_np(attr);
	posix_spawn_destroypersona_info_np(attr);

	free(psattr);
	*attr = NULL;

	return (0);
}