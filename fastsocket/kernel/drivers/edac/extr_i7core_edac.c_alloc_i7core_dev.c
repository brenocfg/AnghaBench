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
typedef  int /*<<< orphan*/  u8 ;
struct pci_id_table {int n_devs; } ;
struct i7core_dev {int n_devs; int /*<<< orphan*/  list; int /*<<< orphan*/  socket; void* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  i7core_edac_list ; 
 int /*<<< orphan*/  kfree (struct i7core_dev*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct i7core_dev *alloc_i7core_dev(u8 socket,
					   const struct pci_id_table *table)
{
	struct i7core_dev *i7core_dev;

	i7core_dev = kzalloc(sizeof(*i7core_dev), GFP_KERNEL);
	if (!i7core_dev)
		return NULL;

	i7core_dev->pdev = kzalloc(sizeof(*i7core_dev->pdev) * table->n_devs,
				   GFP_KERNEL);
	if (!i7core_dev->pdev) {
		kfree(i7core_dev);
		return NULL;
	}

	i7core_dev->socket = socket;
	i7core_dev->n_devs = table->n_devs;
	list_add_tail(&i7core_dev->list, &i7core_edac_list);

	return i7core_dev;
}