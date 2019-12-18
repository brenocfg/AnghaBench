#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  qlen; } ;
struct TYPE_7__ {int /*<<< orphan*/  qlen; } ;
struct TYPE_6__ {int /*<<< orphan*/  qlen; } ;
struct TYPE_5__ {int /*<<< orphan*/  qlen; } ;
struct skb_pool {int /*<<< orphan*/  clone_slab_hit; int /*<<< orphan*/  clone_pool_hit; TYPE_4__ clone_recyc_list; TYPE_3__ clone_free_list; int /*<<< orphan*/  slab_hit; int /*<<< orphan*/  pool_hit; TYPE_2__ recyc_list; TYPE_1__ free_list; } ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_id ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skb_pool_seq_show(struct seq_file *seq, void *v)
{
	struct skb_pool *s = v;

	seq_printf(seq, "%u\t%-15u%-15u%-15lu%-15lu%-15u%-15u%-15lu%-15lu\n",
		cpu_id, s->free_list.qlen, s->recyc_list.qlen,
		s->pool_hit, s->slab_hit,
		s->clone_free_list.qlen, s->clone_recyc_list.qlen,
		s->clone_pool_hit, s->clone_slab_hit);

	return 0;
}