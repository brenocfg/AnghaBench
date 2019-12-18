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
struct TYPE_3__ {scalar_t__ submod_enabled; } ;
struct bfa_s {TYPE_1__ iocfc; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* iocdisable ) (struct bfa_s*) ;} ;

/* Variables and functions */
 scalar_t__ BFA_FALSE ; 
 TYPE_2__** hal_mods ; 
 int /*<<< orphan*/  stub1 (struct bfa_s*) ; 

__attribute__((used)) static void
bfa_iocfc_disable_submod(struct bfa_s *bfa)
{
	int		i;

	if (bfa->iocfc.submod_enabled == BFA_FALSE)
		return;

	for (i = 0; hal_mods[i]; i++)
		hal_mods[i]->iocdisable(bfa);

	bfa->iocfc.submod_enabled = BFA_FALSE;
}