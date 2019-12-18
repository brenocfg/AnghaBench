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
 int _VAC_IN_GROUP ; 
 int vauth_node_group (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int
vauth_file_ingroup(vauth_ctx vcp, int *ismember, int idontknow)
{
	int	error;

	/* Check for a cached answer first, to avoid the check if possible */
	if (vcp->flags_valid & _VAC_IN_GROUP) {
		*ismember = (vcp->flags & _VAC_IN_GROUP) ? 1 : 0;
		error = 0;
	} else {
		/* Otherwise, go look for it */
		error = vauth_node_group(vcp->vap, vcp->ctx->vc_ucred, ismember, idontknow);

		if (!error) {
			/* cache our result */
			vcp->flags_valid |= _VAC_IN_GROUP;
			if (*ismember) {
				vcp->flags |= _VAC_IN_GROUP;
			} else {
				vcp->flags &= ~_VAC_IN_GROUP;
			}
		}
		
	}
	return(error);
}