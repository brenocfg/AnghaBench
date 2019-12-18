#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sym_tcb {int usrtags; int usr_width; int /*<<< orphan*/  usr_period; int /*<<< orphan*/  usrflags; } ;
struct Tekram_target {int flags; int sync_index; } ;
struct TYPE_3__ {int max_tags_index; struct Tekram_target* target; } ;
typedef  TYPE_1__ Tekram_nvram ;

/* Variables and functions */
 int /*<<< orphan*/  SYM_DISC_ENABLED ; 
 int TEKRAM_DISCONNECT_ENABLE ; 
 int TEKRAM_SYNC_NEGO ; 
 int TEKRAM_TAGGED_COMMANDS ; 
 int TEKRAM_WIDE_NEGO ; 
 int /*<<< orphan*/ * Tekram_sync ; 

__attribute__((used)) static void
sym_Tekram_setup_target(struct sym_tcb *tp, int target, Tekram_nvram *nvram)
{
	struct Tekram_target *tn = &nvram->target[target];

	if (tn->flags & TEKRAM_TAGGED_COMMANDS) {
		tp->usrtags = 2 << nvram->max_tags_index;
	}

	if (tn->flags & TEKRAM_DISCONNECT_ENABLE)
		tp->usrflags |= SYM_DISC_ENABLED;
 
	if (tn->flags & TEKRAM_SYNC_NEGO)
		tp->usr_period = Tekram_sync[tn->sync_index & 0xf];
	tp->usr_width = (tn->flags & TEKRAM_WIDE_NEGO) ? 1 : 0;
}