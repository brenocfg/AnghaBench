#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_2__ {int /*<<< orphan*/  zo_raidz_parity; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  UMEM_NOFAIL ; 
 int /*<<< orphan*/  VDEV_TYPE_RAIDZ ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_CHILDREN ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_NPARITY ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_TYPE ; 
 int /*<<< orphan*/ * make_vdev_file (char*,char*,char*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_add_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 scalar_t__ nvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** umem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umem_free (int /*<<< orphan*/ **,int) ; 
 TYPE_1__ ztest_opts ; 

__attribute__((used)) static nvlist_t *
make_vdev_raidz(char *path, char *aux, char *pool, size_t size,
    uint64_t ashift, int r)
{
	nvlist_t *raidz, **child;
	int c;

	if (r < 2)
		return (make_vdev_file(path, aux, pool, size, ashift));
	child = umem_alloc(r * sizeof (nvlist_t *), UMEM_NOFAIL);

	for (c = 0; c < r; c++)
		child[c] = make_vdev_file(path, aux, pool, size, ashift);

	VERIFY(nvlist_alloc(&raidz, NV_UNIQUE_NAME, 0) == 0);
	VERIFY(nvlist_add_string(raidz, ZPOOL_CONFIG_TYPE,
	    VDEV_TYPE_RAIDZ) == 0);
	VERIFY(nvlist_add_uint64(raidz, ZPOOL_CONFIG_NPARITY,
	    ztest_opts.zo_raidz_parity) == 0);
	VERIFY(nvlist_add_nvlist_array(raidz, ZPOOL_CONFIG_CHILDREN,
	    child, r) == 0);

	for (c = 0; c < r; c++)
		nvlist_free(child[c]);

	umem_free(child, r * sizeof (nvlist_t *));

	return (raidz);
}