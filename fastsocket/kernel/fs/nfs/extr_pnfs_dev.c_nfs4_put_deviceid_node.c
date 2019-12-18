#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nfs4_deviceid_node {TYPE_1__* ld; int /*<<< orphan*/  ref; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free_deviceid_node ) (struct nfs4_deviceid_node*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct nfs4_deviceid_node*) ; 

bool
nfs4_put_deviceid_node(struct nfs4_deviceid_node *d)
{
	if (!atomic_dec_and_test(&d->ref))
		return false;
	d->ld->free_deviceid_node(d);
	return true;
}