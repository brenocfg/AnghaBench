#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
struct nfs_cache_array {int size; TYPE_2__* array; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__ string; } ;

/* Variables and functions */
 int /*<<< orphan*/  KM_USER0 ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct nfs_cache_array* kmap_atomic (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (struct nfs_cache_array*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void nfs_readdir_clear_array(struct page *page)
{
	struct nfs_cache_array *array;
	int i;

	array = kmap_atomic(page, KM_USER0);
	for (i = 0; i < array->size; i++)
		kfree(array->array[i].string.name);
	kunmap_atomic(array, KM_USER0);
}