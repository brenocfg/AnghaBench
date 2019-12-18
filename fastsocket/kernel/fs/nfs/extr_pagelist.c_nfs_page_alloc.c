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
struct nfs_page {int /*<<< orphan*/  wb_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct nfs_page* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct nfs_page*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfs_page_cachep ; 

__attribute__((used)) static inline struct nfs_page *
nfs_page_alloc(void)
{
	struct nfs_page	*p;
	p = kmem_cache_alloc(nfs_page_cachep, GFP_KERNEL);
	if (p) {
		memset(p, 0, sizeof(*p));
		INIT_LIST_HEAD(&p->wb_list);
	}
	return p;
}