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
typedef  int /*<<< orphan*/  u16 ;
struct bfa_throttle_cfg_s {int is_valid; int /*<<< orphan*/  value; } ;
struct bfa_s {int dummy; } ;
struct TYPE_4__ {TYPE_1__* dconf; } ;
struct TYPE_3__ {struct bfa_throttle_cfg_s throttle_cfg; } ;

/* Variables and functions */
 TYPE_2__* BFA_DCONF_MOD (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_dconf_get_min_cfg (struct bfa_s*) ; 

u16
bfa_fcpim_read_throttle(struct bfa_s *bfa)
{
	struct bfa_throttle_cfg_s *throttle_cfg =
			&(BFA_DCONF_MOD(bfa)->dconf->throttle_cfg);

	return ((!bfa_dconf_get_min_cfg(bfa)) ?
	       ((throttle_cfg->is_valid == 1) ? (throttle_cfg->value) : 0) : 0);
}