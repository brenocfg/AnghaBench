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
struct rds_page_frag {int /*<<< orphan*/  f_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct rds_page_frag*) ; 
 int /*<<< orphan*/  rds_iw_frag_slab ; 
 int /*<<< orphan*/  rdsdebug (char*,struct rds_page_frag*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rds_iw_frag_free(struct rds_page_frag *frag)
{
	rdsdebug("frag %p page %p\n", frag, frag->f_page);
	BUG_ON(frag->f_page);
	kmem_cache_free(rds_iw_frag_slab, frag);
}