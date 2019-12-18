#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  Id; int /*<<< orphan*/  list; } ;
typedef  TYPE_1__ udiva_card ;
typedef  int /*<<< orphan*/  diva_os_spin_lock_magic_t ;
typedef  int /*<<< orphan*/  DESCRIPTOR ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_ERR (char*) ; 
 int /*<<< orphan*/  DBG_LOG (char*) ; 
 int /*<<< orphan*/  diva_os_enter_spin_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  diva_os_free (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  diva_os_leave_spin_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  diva_user_mode_idi_remove_adapter (int /*<<< orphan*/ ) ; 
 TYPE_1__* find_card_in_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ll_lock ; 

__attribute__((used)) static void um_remove_card(DESCRIPTOR * d)
{
	diva_os_spin_lock_magic_t old_irql;
	udiva_card *card = NULL;

	if (!(card = find_card_in_list(d))) {
		DBG_ERR(("cannot find card to remove"));
		return;
	}
	diva_user_mode_idi_remove_adapter(card->Id);
	diva_os_enter_spin_lock(&ll_lock, &old_irql, "remove card");
	list_del(&card->list);
	diva_os_leave_spin_lock(&ll_lock, &old_irql, "remove card");
	DBG_LOG(("idi proc entry removed for card %d", card->Id));
	diva_os_free(0, card);
}