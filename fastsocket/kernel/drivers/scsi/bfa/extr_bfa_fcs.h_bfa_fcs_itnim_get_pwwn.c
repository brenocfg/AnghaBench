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
typedef  int /*<<< orphan*/  wwn_t ;
struct bfa_fcs_itnim_s {TYPE_1__* rport; } ;
struct TYPE_2__ {int /*<<< orphan*/  pwwn; } ;

/* Variables and functions */

__attribute__((used)) static inline wwn_t
bfa_fcs_itnim_get_pwwn(struct bfa_fcs_itnim_s *itnim)
{
	return itnim->rport->pwwn;
}