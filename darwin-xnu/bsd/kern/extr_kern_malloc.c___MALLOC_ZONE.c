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
typedef  size_t vm_size_t ;
typedef  int /*<<< orphan*/  vm_allocation_site_t ;
struct kmzones {scalar_t__ kz_zalloczone; size_t kz_elemsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ KMZ_MALLOC ; 
 int M_LAST ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bzero (void*,size_t) ; 
 scalar_t__ kalloc_canblock (size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct kmzones* kmzones ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 scalar_t__ zalloc (scalar_t__) ; 
 scalar_t__ zalloc_noblock (scalar_t__) ; 

void *
__MALLOC_ZONE(
	size_t		size,
	int		type,
	int		flags,
	vm_allocation_site_t *site)
{
	struct kmzones	*kmz;
	void		*elem;

	if (type >= M_LAST)
		panic("_malloc_zone TYPE");

	kmz = &kmzones[type];
	if (kmz->kz_zalloczone == KMZ_MALLOC)
		panic("_malloc_zone ZONE: type = %d", type);

/* XXX */
	if (kmz->kz_elemsize == (size_t)(-1))
		panic("_malloc_zone XXX");
/* XXX */
	if (size == kmz->kz_elemsize)
		if (flags & M_NOWAIT) {
	  		elem = (void *)zalloc_noblock(kmz->kz_zalloczone);
		} else {
	  		elem = (void *)zalloc(kmz->kz_zalloczone);
		}
	else {
		vm_size_t kalloc_size = size;
		if (size > kalloc_size) {
			elem = NULL;
		} else if (flags & M_NOWAIT) {
			elem = (void *)kalloc_canblock(&kalloc_size, FALSE, site);
		} else {
			elem = (void *)kalloc_canblock(&kalloc_size, TRUE, site);
		}
	}

	if (elem && (flags & M_ZERO))
		bzero(elem, size);

	return (elem);
}