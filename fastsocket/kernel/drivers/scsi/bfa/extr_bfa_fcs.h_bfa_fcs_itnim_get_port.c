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
struct bfa_fcs_lport_s {int dummy; } ;
struct bfa_fcs_itnim_s {TYPE_1__* rport; } ;
struct TYPE_2__ {struct bfa_fcs_lport_s* port; } ;

/* Variables and functions */

__attribute__((used)) static inline struct bfa_fcs_lport_s *
bfa_fcs_itnim_get_port(struct bfa_fcs_itnim_s *itnim)
{
	return itnim->rport->port;
}