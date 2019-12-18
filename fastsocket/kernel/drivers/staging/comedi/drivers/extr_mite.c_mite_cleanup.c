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
struct mite_struct {struct mite_struct* next; int /*<<< orphan*/  pcidev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mite_struct*) ; 
 struct mite_struct* mite_devices ; 
 int /*<<< orphan*/  pci_dev_put (int /*<<< orphan*/ ) ; 

void mite_cleanup(void)
{
	struct mite_struct *mite, *next;

	for (mite = mite_devices; mite; mite = next) {
		pci_dev_put(mite->pcidev);
		next = mite->next;
		kfree(mite);
	}
}