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
struct bfa_s {int /*<<< orphan*/  ioc; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* detach ) (struct bfa_s*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_ioc_detach (int /*<<< orphan*/ *) ; 
 TYPE_1__** hal_mods ; 
 int /*<<< orphan*/  stub1 (struct bfa_s*) ; 

void
bfa_detach(struct bfa_s *bfa)
{
	int	i;

	for (i = 0; hal_mods[i]; i++)
		hal_mods[i]->detach(bfa);
	bfa_ioc_detach(&bfa->ioc);
}