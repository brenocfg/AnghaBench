#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  start; } ;
typedef  TYPE_1__ slram_priv_t ;
struct TYPE_7__ {struct TYPE_7__* mtdinfo; struct TYPE_7__* priv; struct TYPE_7__* next; } ;
typedef  TYPE_2__ slram_mtd_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  del_mtd_device (TYPE_2__*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 TYPE_2__* slram_mtdlist ; 

__attribute__((used)) static void unregister_devices(void)
{
	slram_mtd_list_t *nextitem;

	while (slram_mtdlist) {
		nextitem = slram_mtdlist->next;
		del_mtd_device(slram_mtdlist->mtdinfo);
		iounmap(((slram_priv_t *)slram_mtdlist->mtdinfo->priv)->start);
		kfree(slram_mtdlist->mtdinfo->priv);
		kfree(slram_mtdlist->mtdinfo);
		kfree(slram_mtdlist);
		slram_mtdlist = nextitem;
	}
}