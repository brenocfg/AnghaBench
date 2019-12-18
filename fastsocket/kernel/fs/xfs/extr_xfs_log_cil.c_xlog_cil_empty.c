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
struct xfs_cil {int /*<<< orphan*/  xc_cil_lock; int /*<<< orphan*/  xc_cil; } ;
struct log {struct xfs_cil* l_cilp; } ;

/* Variables and functions */
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

bool
xlog_cil_empty(
	struct log	*log)
{
	struct xfs_cil	*cil = log->l_cilp;
	bool		empty = false;

	spin_lock(&cil->xc_cil_lock);
	if (list_empty(&cil->xc_cil))
		empty = true;
	spin_unlock(&cil->xc_cil_lock);
	return empty;
}