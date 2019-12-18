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
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
struct fd_vn_data {scalar_t__ fv_bufdone; scalar_t__ fv_buf; int /*<<< orphan*/  fv_bufsiz; } ;
struct direntry {int dummy; } ;

/* Variables and functions */
 int refill_fd_direntries (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fd_vn_data*,int*) ; 

__attribute__((used)) static int
get_direntry(vfs_context_t ctx, vnode_t dvp, struct fd_vn_data *fvd,
    int *eofflagp, struct direntry **dpp)
{
	int eofflag;
	int error;

	*eofflagp = 0;
	*dpp = NULL;
	error = 0;
	if (!fvd->fv_bufsiz) {
		error = refill_fd_direntries(ctx, dvp, fvd, &eofflag);
		if (error) {
			return (error);
		}
		if (eofflag) {
			*eofflagp = eofflag;
			return (error);
		}
	}

	*dpp = (struct direntry *)(fvd->fv_buf + fvd->fv_bufdone);
	return (error);
}