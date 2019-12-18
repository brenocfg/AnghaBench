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
struct page {int dummy; } ;
typedef  void nfs_cache_array ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 void* kmap (struct page*) ; 

__attribute__((used)) static
struct nfs_cache_array *nfs_readdir_get_array(struct page *page)
{
	void *ptr;
	if (page == NULL)
		return ERR_PTR(-EIO);
	ptr = kmap(page);
	if (ptr == NULL)
		return ERR_PTR(-ENOMEM);
	return ptr;
}