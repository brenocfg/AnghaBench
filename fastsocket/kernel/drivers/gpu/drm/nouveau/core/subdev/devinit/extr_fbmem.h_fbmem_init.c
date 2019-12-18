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
struct pci_dev {int dummy; } ;
struct io_mapping {int dummy; } ;

/* Variables and functions */
 struct io_mapping* io_mapping_create_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_resource_start (struct pci_dev*,int) ; 

__attribute__((used)) static inline struct io_mapping *
fbmem_init(struct pci_dev *pdev)
{
	return io_mapping_create_wc(pci_resource_start(pdev, 1),
				    pci_resource_len(pdev, 1));
}