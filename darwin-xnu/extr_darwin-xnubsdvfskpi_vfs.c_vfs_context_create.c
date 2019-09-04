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
typedef  int /*<<< orphan*/  kauth_cred_t ;
struct TYPE_4__ {int /*<<< orphan*/  vc_ucred; int /*<<< orphan*/  vc_thread; } ;

/* Variables and functions */
 scalar_t__ IS_VALID_CRED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_thread () ; 
 scalar_t__ kalloc (int) ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 int /*<<< orphan*/  kauth_cred_ref (int /*<<< orphan*/ ) ; 

vfs_context_t
vfs_context_create(vfs_context_t ctx)
{
	vfs_context_t newcontext;

	newcontext = (vfs_context_t)kalloc(sizeof(struct vfs_context));

	if (newcontext) {
		kauth_cred_t safecred;
		if (ctx) {
			newcontext->vc_thread = ctx->vc_thread;
			safecred = ctx->vc_ucred;
		} else {
			newcontext->vc_thread = current_thread();
			safecred = kauth_cred_get();
		}
		if (IS_VALID_CRED(safecred))
			kauth_cred_ref(safecred);
		newcontext->vc_ucred = safecred;
		return(newcontext);
	}
	return(NULL);	
}