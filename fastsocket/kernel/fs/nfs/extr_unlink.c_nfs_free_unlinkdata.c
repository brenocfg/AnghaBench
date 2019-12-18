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
struct TYPE_3__ {struct nfs_unlinkdata* name; } ;
struct TYPE_4__ {TYPE_1__ name; } ;
struct nfs_unlinkdata {TYPE_2__ args; int /*<<< orphan*/  cred; int /*<<< orphan*/  dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  iput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nfs_unlinkdata*) ; 
 int /*<<< orphan*/  put_rpccred (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nfs_free_unlinkdata(struct nfs_unlinkdata *data)
{
	iput(data->dir);
	put_rpccred(data->cred);
	kfree(data->args.name.name);
	kfree(data);
}