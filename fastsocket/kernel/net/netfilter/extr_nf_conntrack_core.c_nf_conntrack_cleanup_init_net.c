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
struct TYPE_3__ {int /*<<< orphan*/  use; } ;
struct TYPE_4__ {TYPE_1__ ct_general; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_conntrack_helper_fini () ; 
 int /*<<< orphan*/  nf_conntrack_proto_fini () ; 
 TYPE_2__ nf_conntrack_untracked ; 
 int /*<<< orphan*/  schedule () ; 

__attribute__((used)) static void nf_conntrack_cleanup_init_net(void)
{
	/* wait until all references to nf_conntrack_untracked are dropped */
	while (atomic_read(&nf_conntrack_untracked.ct_general.use) > 1)
		schedule();

	nf_conntrack_helper_fini();
	nf_conntrack_proto_fini();
}