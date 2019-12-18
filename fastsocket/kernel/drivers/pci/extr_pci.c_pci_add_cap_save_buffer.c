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
struct pci_dev {int dummy; } ;
struct TYPE_2__ {char cap_nr; unsigned int size; } ;
struct pci_cap_saved_state {TYPE_1__ cap; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct pci_cap_saved_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_add_saved_cap (struct pci_dev*,struct pci_cap_saved_state*) ; 
 int pci_find_capability (struct pci_dev*,char) ; 

__attribute__((used)) static int pci_add_cap_save_buffer(
	struct pci_dev *dev, char cap, unsigned int size)
{
	int pos;
	struct pci_cap_saved_state *save_state;

	pos = pci_find_capability(dev, cap);
	if (pos <= 0)
		return 0;

	save_state = kzalloc(sizeof(*save_state) + size, GFP_KERNEL);
	if (!save_state)
		return -ENOMEM;

	save_state->cap.cap_nr = cap;
	save_state->cap.size = size;
	pci_add_saved_cap(dev, save_state);

	return 0;
}