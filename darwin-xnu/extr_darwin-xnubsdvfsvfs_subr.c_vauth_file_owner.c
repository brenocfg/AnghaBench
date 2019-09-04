#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vauth_ctx ;
struct TYPE_5__ {int flags_valid; int flags; TYPE_1__* ctx; int /*<<< orphan*/  vap; } ;
struct TYPE_4__ {int /*<<< orphan*/  vc_ucred; } ;

/* Variables and functions */
 int _VAC_IS_OWNER ; 
 int vauth_node_owner (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vauth_file_owner(vauth_ctx vcp)
{
	int result;

	if (vcp->flags_valid & _VAC_IS_OWNER) {
		result = (vcp->flags & _VAC_IS_OWNER) ? 1 : 0;
	} else {
		result = vauth_node_owner(vcp->vap, vcp->ctx->vc_ucred);

		/* cache our result */
		vcp->flags_valid |= _VAC_IS_OWNER;
		if (result) {
			vcp->flags |= _VAC_IS_OWNER;
		} else {
			vcp->flags &= ~_VAC_IS_OWNER;
		}
	}
	return(result);
}