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
struct yenta_socket {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  subordinate; } ;

/* Variables and functions */
 int IORESOURCE_IO ; 
 int IORESOURCE_MEM ; 
 int IORESOURCE_PREFETCH ; 
 int /*<<< orphan*/  PCI_CB_IO_BASE_0 ; 
 int /*<<< orphan*/  PCI_CB_IO_BASE_1 ; 
 int /*<<< orphan*/  PCI_CB_IO_LIMIT_0 ; 
 int /*<<< orphan*/  PCI_CB_IO_LIMIT_1 ; 
 int /*<<< orphan*/  PCI_CB_MEMORY_BASE_0 ; 
 int /*<<< orphan*/  PCI_CB_MEMORY_BASE_1 ; 
 int /*<<< orphan*/  PCI_CB_MEMORY_LIMIT_0 ; 
 int /*<<< orphan*/  PCI_CB_MEMORY_LIMIT_1 ; 
 int /*<<< orphan*/  pci_setup_cardbus (int /*<<< orphan*/ ) ; 
 scalar_t__ yenta_allocate_res (struct yenta_socket*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void yenta_allocate_resources(struct yenta_socket *socket)
{
	int program = 0;
	program += yenta_allocate_res(socket, 0, IORESOURCE_IO,
			   PCI_CB_IO_BASE_0, PCI_CB_IO_LIMIT_0);
	program += yenta_allocate_res(socket, 1, IORESOURCE_IO,
			   PCI_CB_IO_BASE_1, PCI_CB_IO_LIMIT_1);
	program += yenta_allocate_res(socket, 2, IORESOURCE_MEM|IORESOURCE_PREFETCH,
			   PCI_CB_MEMORY_BASE_0, PCI_CB_MEMORY_LIMIT_0);
	program += yenta_allocate_res(socket, 3, IORESOURCE_MEM,
			   PCI_CB_MEMORY_BASE_1, PCI_CB_MEMORY_LIMIT_1);
	if (program)
		pci_setup_cardbus(socket->dev->subordinate);
}