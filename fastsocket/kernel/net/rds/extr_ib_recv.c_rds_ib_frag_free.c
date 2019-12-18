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
struct rds_page_frag {int /*<<< orphan*/  f_cache_entry; int /*<<< orphan*/  f_sg; } ;
struct rds_ib_connection {int /*<<< orphan*/  i_cache_frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  rds_ib_recv_cache_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdsdebug (char*,struct rds_page_frag*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_page (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rds_ib_frag_free(struct rds_ib_connection *ic,
			     struct rds_page_frag *frag)
{
	rdsdebug("frag %p page %p\n", frag, sg_page(&frag->f_sg));

	rds_ib_recv_cache_put(&frag->f_cache_entry, &ic->i_cache_frags);
}