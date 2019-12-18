#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vfs_context_t ;
struct vfs_context {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  vc_ucred; } ;

/* Variables and functions */
 scalar_t__ IS_VALID_CRED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*,int) ; 

int
vfs_context_rele(vfs_context_t ctx)
{
	if (ctx) {
		if (IS_VALID_CRED(ctx->vc_ucred))
			kauth_cred_unref(&ctx->vc_ucred);
		kfree(ctx, sizeof(struct vfs_context));
	}
	return(0);
}