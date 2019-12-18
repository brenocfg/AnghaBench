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
struct net {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * proc_ent; scalar_t__ content_ent; scalar_t__ channel_ent; scalar_t__ flush_ent; } ;
struct TYPE_3__ {TYPE_2__ procfs; } ;
struct cache_detail {char* name; TYPE_1__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/ * proc_net_rpc ; 
 int /*<<< orphan*/  remove_proc_entry (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void remove_cache_proc_entries(struct cache_detail *cd, struct net *net)
{
	if (cd->u.procfs.proc_ent == NULL)
		return;
	if (cd->u.procfs.flush_ent)
		remove_proc_entry("flush", cd->u.procfs.proc_ent);
	if (cd->u.procfs.channel_ent)
		remove_proc_entry("channel", cd->u.procfs.proc_ent);
	if (cd->u.procfs.content_ent)
		remove_proc_entry("content", cd->u.procfs.proc_ent);
	cd->u.procfs.proc_ent = NULL;
	remove_proc_entry(cd->name, proc_net_rpc);
}