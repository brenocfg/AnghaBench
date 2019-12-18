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
struct t10_alua_tg_pt_gp {int /*<<< orphan*/  tg_pt_gp_ref_cnt; struct se_device* tg_pt_gp_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  tg_pt_gps_lock; } ;
struct se_device {TYPE_1__ t10_alua; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void core_alua_put_tg_pt_gp_from_name(
	struct t10_alua_tg_pt_gp *tg_pt_gp)
{
	struct se_device *dev = tg_pt_gp->tg_pt_gp_dev;

	spin_lock(&dev->t10_alua.tg_pt_gps_lock);
	atomic_dec(&tg_pt_gp->tg_pt_gp_ref_cnt);
	spin_unlock(&dev->t10_alua.tg_pt_gps_lock);
}