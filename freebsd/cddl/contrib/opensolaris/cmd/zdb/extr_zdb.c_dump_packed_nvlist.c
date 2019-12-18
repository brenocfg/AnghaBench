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
typedef  size_t uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMU_READ_PREFETCH ; 
 int /*<<< orphan*/  UMEM_NOFAIL ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ dmu_read (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,size_t,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_nvlist (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_unpack (char*,size_t,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 char* umem_alloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umem_free (char*,size_t) ; 

__attribute__((used)) static void
dump_packed_nvlist(objset_t *os, uint64_t object, void *data, size_t size)
{
	nvlist_t *nv;
	size_t nvsize = *(uint64_t *)data;
	char *packed = umem_alloc(nvsize, UMEM_NOFAIL);

	VERIFY(0 == dmu_read(os, object, 0, nvsize, packed, DMU_READ_PREFETCH));

	VERIFY(nvlist_unpack(packed, nvsize, &nv, 0) == 0);

	umem_free(packed, nvsize);

	dump_nvlist(nv, 8);

	nvlist_free(nv);
}