#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pci_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  bus; } ;
struct TYPE_5__ {unsigned int size; int size_value; } ;
struct TYPE_4__ {struct pci_dev* misc; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD64_GARTAPERTUREBASE ; 
 int ARRAY_SIZE (TYPE_2__*) ; 
 int ENODEV ; 
 int /*<<< orphan*/  NVIDIA_X86_64_0_APBASE ; 
 int /*<<< orphan*/  NVIDIA_X86_64_1_APBASE1 ; 
 int /*<<< orphan*/  NVIDIA_X86_64_1_APBASE2 ; 
 int /*<<< orphan*/  NVIDIA_X86_64_1_APLIMIT1 ; 
 int /*<<< orphan*/  NVIDIA_X86_64_1_APLIMIT2 ; 
 int /*<<< orphan*/  NVIDIA_X86_64_1_APSIZE ; 
 int PCI_BASE_ADDRESS_MEM_MASK ; 
 int /*<<< orphan*/  PCI_DEVFN (int,int /*<<< orphan*/ ) ; 
 unsigned int amd64_fetch_size () ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_2__* nforce3_sizes ; 
 TYPE_1__* node_to_amd_nb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int nforce3_agp_init(struct pci_dev *pdev)
{
	u32 tmp, apbase, apbar, aplimit;
	struct pci_dev *dev1;
	int i;
	unsigned size = amd64_fetch_size();

	dev_info(&pdev->dev, "setting up Nforce3 AGP\n");

	dev1 = pci_get_slot(pdev->bus, PCI_DEVFN(11, 0));
	if (dev1 == NULL) {
		dev_info(&pdev->dev, "can't find Nforce3 secondary device\n");
		return -ENODEV;
	}

	for (i = 0; i < ARRAY_SIZE(nforce3_sizes); i++)
		if (nforce3_sizes[i].size == size)
			break;

	if (i == ARRAY_SIZE(nforce3_sizes)) {
		dev_info(&pdev->dev, "no NForce3 size found for %d\n", size);
		return -ENODEV;
	}

	pci_read_config_dword(dev1, NVIDIA_X86_64_1_APSIZE, &tmp);
	tmp &= ~(0xf);
	tmp |= nforce3_sizes[i].size_value;
	pci_write_config_dword(dev1, NVIDIA_X86_64_1_APSIZE, tmp);

	/* shadow x86-64 registers into NVIDIA registers */
	pci_read_config_dword (node_to_amd_nb(0)->misc, AMD64_GARTAPERTUREBASE,
			       &apbase);

	/* if x86-64 aperture base is beyond 4G, exit here */
	if ( (apbase & 0x7fff) >> (32 - 25) ) {
		dev_info(&pdev->dev, "aperture base > 4G\n");
		return -ENODEV;
	}

	apbase = (apbase & 0x7fff) << 25;

	pci_read_config_dword(pdev, NVIDIA_X86_64_0_APBASE, &apbar);
	apbar &= ~PCI_BASE_ADDRESS_MEM_MASK;
	apbar |= apbase;
	pci_write_config_dword(pdev, NVIDIA_X86_64_0_APBASE, apbar);

	aplimit = apbase + (size * 1024 * 1024) - 1;
	pci_write_config_dword(dev1, NVIDIA_X86_64_1_APBASE1, apbase);
	pci_write_config_dword(dev1, NVIDIA_X86_64_1_APLIMIT1, aplimit);
	pci_write_config_dword(dev1, NVIDIA_X86_64_1_APBASE2, apbase);
	pci_write_config_dword(dev1, NVIDIA_X86_64_1_APLIMIT2, aplimit);

	pci_dev_put(dev1);

	return 0;
}